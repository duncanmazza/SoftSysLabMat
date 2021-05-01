/* Evaluation code
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "evaluate.h"



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

    fprintf(stderr, "Assignment statement evaluation has not yet been "
                    "implemented\n");
    return 1;
}


int evaluate(OTree *otree) {
    switch (otree->type) {
        case OTREE_VAL_PARENT:
            break;
        case OTREE_VAL_STR:
        case OTREE_VAL_LONG:
        case OTREE_VAL_DOUBLE:
        case OTREE_VAL_MAT:
        case OTREE_VAL_BINOP_ENUM:
        case OTREE_DELIM:
            return 0;
        case OTREE_VAL_INDETERMINATE:
            fprintf(stderr, "Encountered undetermined otree value type");
            return 1;
    }

    // This point is only reached if otree->type = OTREE_VAL_PARENT

    DLL_Node *child;
    int recurse_ret;
    switch(otree->label) {
        case LM_LAB_MAT:
            child = otree->children->s->next;
            while (child != otree->children->s) {
                recurse_ret = evaluate((OTree *)child->val);
                if (recurse_ret) return recurse_ret;
                child = child->next;
            }
            return 0;
        case LM_STATEMENT:
            child = otree->children->s->next;
            return evaluate((OTree *)child->val);
        case LM_STATEMENT_ASSIGNMENT:
            return eval_assmt_stmt(otree);
        case LM_FUNCTION_CALL_EXPRESSION:
            return eval_func_call_expr(otree);
        case LM_SIMPLE_EXPRESSION:
            break;
        case LM_ARGUMENT_LIST:
        case LM_ANY_EXPRESSION:
            fprintf(stderr, "evaluate function cannot handle evaluating an otree "
                            "object with a %s or %s label",
                    otree_label_strs[LM_ARGUMENT_LIST],
                    otree_label_strs[LM_ANY_EXPRESSION]);
            return 1;
        default:
            fprintf(stderr, "otree object was classified as being a parent but "
                            "its label of %s does not match", otree_label_strs[otree->label]);
            return 1;
    }

    // This point is only reached if otree->label = LM_SIMPLE_EXPRESSION

    if (otree->children->len < 3) {
        fprintf(stderr, "simple expression was encountered that did not have "
                        "the minimum of 3 children");
        exit(-1);
    }

    // Evaluate expression from right to left; each trio of children should
    // have a middle child that is an operator
    DLL_Node *child_right;
    DLL_Node *child_middle;
    DLL_Node *child_left;

    OTree *otree_right;
    OTree *otree_left;
    OTree *otree_middle;
    OP_Enum operator;
    child_right = otree->children->s->prev;

    do {
        child_middle = child_right->prev;
        child_left = child_middle->prev;
        otree_right = (OTree *) child_right->val;
        otree_middle = (OTree *) child_middle->val;
        otree_left = (OTree *)child_left->val;
        if (otree_middle->type != OTREE_VAL_BINOP_ENUM) {
            fprintf(stderr, "Encountered a middle otree node in an expression "
                            "that was not an operator");
            exit(-1);
        }

        recurse_ret |= evaluate(otree_right);
        recurse_ret |= evaluate(otree_left);
        if (recurse_ret) return recurse_ret;

        operator = *(OP_Enum *)otree_middle->val;
        (*(binop_func_ptrs[operator]))(otree_left, otree_right);

        DLL_remove(otree->children, child_right);
        DLL_NODE_FREE(child_right);
        DLL_remove(otree->children, child_middle);
        DLL_NODE_FREE(child_middle);
        child_right = child_left;
    } while (child_right->prev != otree->children->s);
    return 0;
}
