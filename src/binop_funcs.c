/* Binary operator evaluation functions
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "../include/binop_funcs.h"

// This must correspond exactly to the order as prescribed in OP_Enum
int (*binop_func_ptrs[])(OTree *, OTree *) = {
        binop_arith_add,
        binop_arith_mult,
        binop_arith_div,
        binop_arith_mod,
        binop_bit_and,
        binop_bit_xor,
        binop_bit_or,
        binop_log_and,
        binop_log_or,
        binop_assmt_equal,
};


OTreeValType check_binop_compatibility(
        const OTreeValTypeTrio acceptable[], size_t acceptable_len,
        OTreeValType left, OTreeValType right, int *swap) {
    for (int i = 0; i < acceptable_len; i++) {
        OTreeValTypeTrio trio = acceptable[i];
        if (left == trio.arg1 && right == trio.arg2) {
            *swap = 0;
            return trio.ret_val;
        } else if (left == trio.arg2 && right == trio.arg1) {
            *swap = 1;
            return trio.ret_val;
        }
    }
    return OTREE_VAL_INDETERMINATE;
}


int binop_arith_add(OTree *left, OTree *right) {
    int swap;
    OTreeValType eval_to = check_binop_compatibility(
            binop_add_mult_sub_eval_to, BINOP_ADD_MULT_SUB_EVAL_TO_LEN,
            left->type, right->type, &swap);
    if (eval_to == OTREE_VAL_INDETERMINATE) {
        fprintf(stderr, "Incompatible types for + operator");
        return 1;
    }

    void *new_l_val = swap ? right->val : left->val;
    OTreeValType new_l_type = swap ? right->type : left->type;
    void *new_r_val = swap ? left->val : right->val;
    OTreeValType new_r_type = swap ? left->type : right->type;

    if (new_l_type == OTREE_VAL_LONG && new_r_type == OTREE_VAL_LONG) {
        *(long *)new_l_val = *(long *)new_l_val + *(long *)new_r_val;
    } else if (new_l_type == OTREE_VAL_DOUBLE &&
               (new_r_type == OTREE_VAL_LONG ||
                new_r_type == OTREE_VAL_DOUBLE)) {
        *(double *) new_l_val = *(double *) new_l_val + *(double *) new_r_val;
    } else if (new_l_type == OTREE_VAL_MAT && new_r_type == OTREE_VAL_MAT) {
        new_l_val = (void *) matrix_add((matrix *) new_l_val,
                                        (matrix *) new_r_val);
    } else if (new_l_type == OTREE_VAL_MAT &&
               (new_r_type == OTREE_VAL_LONG ||
                new_r_type == OTREE_VAL_DOUBLE)) {
        new_l_val = (void *) matrix_add_scalar((matrix *) new_l_val,
                                               (float) *(double *) new_r_val);
    } else {
        fprintf(stderr, "Unhandled case in binop_arith_add");
        exit(-1);
    }
    if (swap) left->val = new_l_val;
    left->type = eval_to;
    return 0;
}


int binop_arith_mult(OTree *left, OTree *right) {
    int swap;
    OTreeValType eval_to = check_binop_compatibility(
            binop_add_mult_sub_eval_to, BINOP_ADD_MULT_SUB_EVAL_TO_LEN,
            left->type, right->type, &swap);
    if (eval_to == OTREE_VAL_INDETERMINATE) {
        fprintf(stderr, "Incompatible types for * operator");
        return 1;
    }
    void *new_l_val = swap ? right->val : left->val;
    OTreeValType new_l_type = swap ? right->type : left->type;
    void *new_r_val = swap ? left->val : right->val;
    OTreeValType new_r_type = swap ? left->type : right->type;

    if (new_l_type == OTREE_VAL_LONG && new_r_type == OTREE_VAL_LONG) {
        *(long *)new_l_val = *(long *)new_l_val * *(long *)new_r_val;
    } else if (new_l_type == OTREE_VAL_DOUBLE &&
               (new_r_type == OTREE_VAL_LONG ||
                new_r_type == OTREE_VAL_DOUBLE)) {
        *(double *) new_l_val = *(double *) new_l_val * *(double *) new_r_val;
    } else if (new_l_type == OTREE_VAL_MAT && new_r_type == OTREE_VAL_MAT) {
        new_l_val = (void *) matrix_multiply((matrix *) new_l_val,
                                             (matrix *) new_r_val);
    } else if (new_l_type == OTREE_VAL_MAT &&
               (new_r_type == OTREE_VAL_LONG ||
                new_r_type == OTREE_VAL_DOUBLE)) {
        new_l_val = (void *) matrix_multiply_scalar((matrix *) new_l_val,
                                               (float) *(double *) new_r_val);
    } else {
        fprintf(stderr, "Unhandled case in binop_arith_mult");
        exit(-1);
    }
    if (swap) left->val = new_l_val;
    left->type = eval_to;
    return 0;
}


int binop_arith_div(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: /");
    return 1;
}


int binop_arith_mod(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: %%");
    return 1;
}


int binop_bit_and(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: &");
    return 1;
}


int binop_bit_xor(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: ^");
    return 1;
}


int binop_bit_or(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: |");
    return 1;
}


int binop_log_and(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: &&");
    return 1;
}


int binop_log_or(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: ||");
    return 1;
}


int binop_assmt_equal(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: =");
    return 1;
}
