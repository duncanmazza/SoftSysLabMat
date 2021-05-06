/* Evaluation code
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "evaluate.h"


HashTable *workspace;
HashTable *var_name_to_str_hash;


int eval_func_call(OTree *otree) {
    if (otree->label == LM_METHOD) {
        DLL_Node *lval_node = otree->children->s->next;
        OTree *lval = (OTree *) lval_node->val;
        DLL_Node *rval_node = lval_node->next->next;
        OTree *rval = (OTree *) rval_node->val;

        OTree *argument_list = ((OTree *) rval->children->s->next->next->val);
        if (!argument_list) {
            argument_list = rval->children->s->next->next->val =
                    make_empty_otree();
            argument_list->label = LM_ARGUMENT_LIST;
            argument_list->type = OTREE_VAL_PARENT;
            argument_list->children = DLL_create();
        }

        if (argument_list->children->len != 0) {
            OTree *delimiter = make_empty_otree();
            delimiter->label = LM_ARGUMENT_LIST_DELIMITER;
            delimiter->type = OTREE_VAL_DELIM;
            DLL_insert(argument_list->children, delimiter);
        }

        int recurse_ret = evaluate(lval);
        if (recurse_ret) return recurse_ret;

        // Insert variable whose method was invoked as the first argument to the
        // function.
        // TODO: check whether the invoked method belongs to the object.
        DLL_insert(argument_list->children, lval);

        recurse_ret = evaluate(rval);
        if (recurse_ret) return recurse_ret;
        child_replace_current(rval_node, otree);

        // TODO: do memory cleanup
        return 0;
    }

    // If this point is reached, then otree is a function call

    DLL_Node *func_otree_node = otree->children->s->next;
    OTree *func_otree = (OTree *) func_otree_node->val;
    DLL_Node *arg_list_otree_node = func_otree_node->next;
    OTree *arg_list_otree = (OTree *) arg_list_otree_node->val;

    // Because of how mpc collapses the abstract syntax tree hierarchy and how
    // our code processes it, single arguments populate not the argument list
    // but the argument list node itself. Address this here by creating an
    // argument list
    if (arg_list_otree->type != OTREE_VAL_PARENT) {
        DLL *arg_list_dll = DLL_create();
        DLL_insert(arg_list_dll, arg_list_otree);
        arg_list_otree = make_empty_otree();
        arg_list_otree->val = NULL;
        arg_list_otree->children = arg_list_dll;
        arg_list_otree->type = OTREE_VAL_PARENT;
        arg_list_otree->label = LM_ARGUMENT_LIST;
        arg_list_otree_node->val = arg_list_otree;
    }

    // Get the function pointer
    char *func_name = (char *) func_otree->val;
    void *(*func_ptr)(size_t, OTree *[]);
    int ht_ret = HT_get(builtins, (HT_KEY_TYPE) func_name, (void **) &func_ptr);
    if (ht_ret) {
        fprintf(stderr, "No function named %s", func_name);
        return 1;
    }

    // Turn linked list of arguments into an array
    size_t nargs = arg_list_otree->children->len / 2 + 1;
    OTree **arg_list = (OTree **) malloc(sizeof(OTree *) * nargs);
    DLL_Node *arg = arg_list_otree->children->s->next;
    int recurse_ret;
    for (int i = 0; i < nargs; i++) {
        recurse_ret = evaluate((OTree *) arg->val);
        if (recurse_ret) return recurse_ret;
        arg_list[i] = (OTree *) arg->val;
        arg = arg->next->next;  // Skip over delimiter
    }

    OTree *ret_val;
    ret_val = (OTree *) func_ptr(nargs, arg_list);
    func_otree_node->val = ret_val;
    child_replace_current(func_otree_node, otree);
    return 0;
}


int replace_var_name_with_var(OTree *otree) {
    OTree *to_replace_with;
    int not_a_var = HT_get(workspace, (HT_KEY_TYPE) otree->val,
                           (void **) &to_replace_with);
    if (not_a_var) {
        fprintf(stderr, "%s does not exist in the workspace",
                (char *) otree->val);
        return not_a_var;
    }
    *otree = *to_replace_with;
    return 0;
}


int evaluate(OTree *otree) {
    int recurse_ret = 0;
    switch (otree->type) {
        case OTREE_VAL_PARENT:
            break;
        case OTREE_VAL_LONG:
        case OTREE_VAL_DOUBLE:
        case OTREE_VAL_MAT:
        case OTREE_VAL_BINOP_ENUM:
        case OTREE_VAL_DELIM:
            return 0;
        case OTREE_VAL_STR:
            if (otree->label == LM_STRING_LITERAL) return 0;
            else return replace_var_name_with_var(otree);
        case OTREE_VAL_INDETERMINATE:
            fprintf(stderr, "Encountered undetermined otree value type");
            return 1;
    }

    // This point is only reached if otree->type = OTREE_VAL_PARENT

    DLL_Node *child;

    switch (otree->label) {
        case LM_LAB_MAT:
            child = otree->children->s->next;
            while (child != otree->children->s) {
                recurse_ret = evaluate((OTree *) child->val);
                if (recurse_ret) return recurse_ret;
                child = child->next;
            }
            return 0;
        case LM_STATEMENT:
            child = otree->children->s->next;
            recurse_ret = evaluate((OTree *) child->val);
            if (recurse_ret) return recurse_ret;
            child_replace_current(child, otree);
            return 0;
        case LM_FUNCTION_CALL_EXPRESSION:
        case LM_METHOD:
            return eval_func_call(otree);
        case LM_STATEMENT_ASSIGNMENT:
        case LM_SIMPLE_EXPRESSION:
            break;
        case LM_ARGUMENT_LIST:
        case LM_ANY_EXPRESSION:
            if (otree->children) { if (otree->children->len == 1) break; }
            fprintf(stderr,
                    "evaluate function cannot handle evaluating an otree "
                    "object with a %s label or a %s label where there is some "
                    "number of children other than 1",
                    otree_label_strs[LM_ARGUMENT_LIST],
                    otree_label_strs[LM_ANY_EXPRESSION]);
            return 1;
        default:
            fprintf(stderr, "otree object was classified as being a parent but "
                            "its label of %s does not match",
                    otree_label_strs[otree->label]);
            return 1;
    }

    // This point is only reached if otree->label = LM_STATEMENT_ASSIGNMENT or
    // LM_SIMPLE_EXPRESSION (or if there is a simple expression that only has
    // one child node and is therefore ambiguously labeled as
    // "LM_ANY_EXPRESSION" based on how mpc rolls tree levels with one child
    // into one hierarchical level)

    // Evaluate expression from right to left; each trio of children should
    // have a middle child that is an operator
    DLL_Node *child_right;
    DLL_Node *child_middle;
    DLL_Node *child_left;

    OTree *otree_right;
    OTree *otree_middle;
    OTree *otree_left;

    int otree_right_is_rvalue;
    int otree_left_is_rvalue;
    OPEnum operator;

    child_right = otree->children->s->prev;
    if (child_right->prev == otree->children->s) {
        otree_right = (OTree *) child_right->val;
        recurse_ret |= evaluate(otree_right);
        if (recurse_ret) return recurse_ret;
        child_replace_current(child_right, otree);
        return 0;
    }

    do {
        child_middle = child_right->prev;
        child_left = child_middle->prev;

        otree_right = (OTree *) child_right->val;
        otree_middle = (OTree *) child_middle->val;
        otree_left = (OTree *) child_left->val;

        otree_right_is_rvalue = otree_right->label != LM_TOKEN_NAME;
        otree_left_is_rvalue = otree_left->label != LM_TOKEN_NAME;

        recurse_ret |= evaluate(otree_right);
        if (otree->label != LM_STATEMENT_ASSIGNMENT)
            recurse_ret |= evaluate(otree_left);
        if (recurse_ret) return recurse_ret;

        operator = *(OPEnum *) otree_middle->val;
        OTree *ret = make_empty_otree();
        recurse_ret |= (*(binop_func_ptrs[operator]))(otree_left, otree_right,
                                                      ret);
        if (recurse_ret) return recurse_ret;

        DLL_remove(otree->children, child_right);
        DLL_remove(otree->children, child_middle);
        DLL_remove(otree->children, child_left);

        if (otree_right_is_rvalue) free(otree_right->val);
        if (otree_left_is_rvalue) free(otree_left->val);
        free(otree_middle->val);

        DLL_NODE_FREE(child_right);
        DLL_NODE_FREE(child_middle);

        child_left->val = ret;
        child_right = child_left;
    } while (child_right->prev != otree->children->s);

    child_replace_current(child_left, otree);
    return 0;
}


void child_replace_current(DLL_Node *const child, OTree *const current) {
    OTree *child_otree = (OTree *) child->val;
    current->val = child_otree->val;
    current->label = child_otree->label;
    current->type = child_otree->type;

    DLL_NODE_FREE(child);  // Also frees otree_child
    current->children = NULL;
}


void print_workspace() {
    printf("\nWorkspace:\n----------\n");
    for (int i = 0; i < workspace->n_slots; i++) {
        DLL *slot = workspace->slots[i];
        DLL_Node *slot_node = slot->s->next;
        while (slot_node != slot->s) {
            DLL *disp_dll = DLL_create();
            HashTableKVP *kvp = (HashTableKVP *) slot_node->val;
            OTree *kvp_otree = (OTree *) kvp->value;
            disp_otree_recursive(kvp_otree, disp_dll, 0);
            SLL *disp_sll = DLL_to_SLL(disp_dll);
            char *disp_str = sll_strs_to_str(disp_sll, "", "");

            void *var_name;
            HT_get_by_str_hash(var_name_to_str_hash, kvp->key, &var_name);

            printf("> %s (%s): %s\n", (char *) var_name,
                   otree_val_type_enum_strs[kvp_otree->type],
                   disp_str + 2);

            free(disp_str);
            DLL_clean(disp_dll);
            DLL_FREE(disp_dll);

            // Manually free each sll node because disp_sll is a shallow copy of
            // disp_dll and SLL_clean would result in a double free.
            SLL_Node *sll_node = disp_sll->head;
            SLL_Node *tmp;
            while (sll_node) {
                tmp = sll_node->next;
                free(sll_node);
                sll_node = tmp;
            }

            free(disp_sll);
            slot_node = slot_node->next;
        }
    }
    printf("\n");
}
