/* Evaluation code
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "evaluate.h"


HashTable *workspace;
HashTable *var_name_to_str_hash;


int eval_func_call_expr(OTree *otree) {
    if (otree->label != LM_FUNCTION_CALL_EXPRESSION) {
        fprintf(stderr, "Attempted to evaluate an otree object as a function "
                        "call expression but it was labeled in stead as %s\n",
                otree_label_strs[otree->label]);
        exit(-1);
    }

    fprintf(stderr, "Function call expression evaluation has not yet "
                    "been implemented\n");
    return 1;
}


int eval_assmt_stmt(OTree *otree) {
    if (otree->label != LM_STATEMENT_ASSIGNMENT) {
        fprintf(stderr, "Attempted to evaluate an otree object as an "
                        "assignment statement but it was labeled in stead as %s\n",
                otree_label_strs[otree->label]);
        exit(-1);
    }

    DLL_Node *child_left = otree->children->s->next;
    DLL_Node *child_middle = child_left->next;
    DLL_Node *child_right = child_middle->next;

    OTree *otree_left = (OTree *) child_left->val;
    OTree *otree_middle = (OTree *) child_middle->val;
    OTree *otree_right = (OTree *) child_right->val;

    HT_KEY_TYPE var_name = (HT_KEY_TYPE) otree_left->val;
    OTree *var_address;
    if (HT_get(workspace, var_name, (void *) &var_address)) {
        var_address = make_empty_otree();
        HT_insert(workspace, var_name, var_address);
        HT_insert(var_name_to_str_hash, var_name,
                  format_msg("%s", CTYPE_STR, 1, 1, otree_left->val));
    }

    OPEnum operator = *(OPEnum *) otree_middle->val;

    switch (operator) {
        case BINOP_ASSMT_EQUAL:
            break;
        default:
            fprintf(stderr, "Operator %s not supported for assignment",
                    binop_enum_strs[operator]);
            exit(-1);
    }

    // This point is only reached if the operator is "="

    int recurse_ret = evaluate(otree_right);
    if (recurse_ret) return recurse_ret;

    var_address->val = otree_right->val;
    var_address->label = otree_right->label;
    var_address->type = otree_right->type;

    free(otree_left->val);
    free(otree_middle->val);
    DLL_NODE_FREE(child_left);
    DLL_NODE_FREE(child_middle);
    child_replace_current(child_right, otree);
    return 0;
}


int replace_var_name_with_var(OTree *otree) {
    OTree *to_replace_with;
    int not_a_var = HT_get(workspace, (HT_KEY_TYPE)otree->val,
                           (void **)&to_replace_with);
    if (not_a_var) {
        fprintf(stderr, "%s does not exist in the workspace", (char *)otree->val);
        return not_a_var;
    }
    otree->label = to_replace_with->label;
    otree->type = to_replace_with->type;
    otree->val = to_replace_with->val;
    return 0;
}


int evaluate(OTree *otree) {
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
    int recurse_ret = 0;
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
        case LM_STATEMENT_ASSIGNMENT:
            return eval_assmt_stmt(otree);
        case LM_FUNCTION_CALL_EXPRESSION:
            return eval_func_call_expr(otree);
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

    // This point is only reached if otree->label = LM_SIMPLE_EXPRESSION (or if
    // there is a simple expression that only has one child node and is
    // therefore ambiguously labeled as "LM_ANY_EXPRESSION" based on how mpc
    // rolls tree levels with one child into one hierarchical level)

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
        otree_right = (OTree *)child_right->val;
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

        if (otree_middle->type != OTREE_VAL_BINOP_ENUM) {
            fprintf(stderr, "Encountered a middle otree node in an expression "
                            "that was not an operator");
            exit(-1);
        }

        recurse_ret |= evaluate(otree_right);
        recurse_ret |= evaluate(otree_left);
        if (recurse_ret) return recurse_ret;

        operator = *(OPEnum *) otree_middle->val;
        OTree *ret = make_empty_otree();
        (*(binop_func_ptrs[operator]))(otree_left, otree_right, ret);

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
