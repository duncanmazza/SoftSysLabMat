/* Binary operator evaluation functions
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "../include/binop_funcs.h"

// This must correspond exactly to the order as prescribed in OP_Enum
int (*binop_func_ptrs[])(OTree *, OTree *, OTree *) = {
        binop_arith_add,
        binop_arith_sub,
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


OTreeValType check_binop_compatibility(const OTreeValTypeTrio acceptable[],
                                       size_t acceptable_len, OTreeValType left,
                                       OTreeValType right, int *swap) {
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


int binop_arith_add(OTree *left, OTree *right, OTree *ret) {
    int swap;
    ret->val = malloc(sizeof(void *));
    OTreeValType eval_to = check_binop_compatibility(
            binop_add_mult_sub_eval_to, BINOP_ADD_MULT_SUB_EVAL_TO_LEN,
            left->type, right->type, &swap);
    if (eval_to == OTREE_VAL_INDETERMINATE) {
        fprintf(stderr, "Incompatible types for + operator\n");
        return 1;
    }

    void *new_l_val;
    void *new_r_val;
    OTreeValType new_l_type;
    OTreeValType new_r_type;
    RESOLVE_VAL_SWAP(new_l_val, new_l_type, new_r_val, new_r_type, right, left,
                     swap);

    if (new_l_type == OTREE_VAL_LONG && new_r_type == OTREE_VAL_LONG) {
        *(long *) ret->val = *(long *) new_l_val + *(long *) new_r_val;
    } else if (new_l_type == OTREE_VAL_DOUBLE) {
        *(double *) ret->val = *(double *) new_l_val +
                               (new_r_type == OTREE_VAL_LONG ?
                                ((double) *(long *) new_r_val) :
                                (*(double *) new_r_val));
    } else if (new_l_type == OTREE_VAL_MAT && new_r_type == OTREE_VAL_MAT) {
        ret->val = (void *) matrix_add((matrix *) new_l_val,
                                       (matrix *) new_r_val);
    } else {
        ret->val = (void *) matrix_add_scalar(
                (matrix *) new_l_val, (float) (
                        new_r_type == OTREE_VAL_LONG ?
                        ((double) *(long *) new_r_val) :
                        (*(double *) new_r_val))
        );
    }

    ret->type = eval_to;
    return 0;
}


int binop_arith_sub(OTree *left, OTree *right, OTree *ret) {
    ret->val = malloc(sizeof(void *));
    int swap;
    OTreeValType eval_to = check_binop_compatibility(
            binop_add_mult_sub_eval_to, BINOP_ADD_MULT_SUB_EVAL_TO_LEN,
            left->type, right->type, &swap);
    if (eval_to == OTREE_VAL_INDETERMINATE) {
        fprintf(stderr, "Incompatible types for + operator\n");
        return 1;
    }

    void *new_l_val;
    void *new_r_val;
    OTreeValType new_l_type;
    OTreeValType new_r_type;
    RESOLVE_VAL_SWAP(new_l_val, new_l_type, new_r_val, new_r_type, right, left,
                     swap);

    // Change negation of left/right values depending on their order

    if (new_l_type == OTREE_VAL_LONG && new_r_type == OTREE_VAL_LONG) {
        *(long *) ret->val = (!swap ? 1 : -1) * *(long *) new_l_val +
                             (!swap ? -1 : 1) * *(long *) new_r_val;
    } else if (new_l_type == OTREE_VAL_DOUBLE) {
        *(double *) ret->val = (!swap ? 1 : -1) * *(double *) new_l_val +
                               (!swap ? -1 : 1) * (new_r_type == OTREE_VAL_LONG
                                                   ? ((double) *(long *) new_r_val)
                                                   : (*(double *) new_r_val));
    } else if (new_l_type == OTREE_VAL_MAT && new_r_type == OTREE_VAL_MAT) {
        ret->val = (void *) matrix_sub((matrix *) new_l_val,
                                       (matrix *) new_r_val);
    } else {
        ret->val = (void *) matrix_add_scalar(
                matrix_multiply_scalar((matrix *) new_l_val,
                                       (!swap ? 1.0f : -1.0f)), (float) (
                        (!swap ? -1 : 1) * (new_r_type == OTREE_VAL_LONG ?
                                            (double) *(long *) new_r_val :
                                            (*(double *) new_r_val)))
        );
    }

    ret->type = eval_to;
    return 0;
}


int binop_arith_mult(OTree *left, OTree *right, OTree *ret) {
    int swap;
    ret->val = malloc(sizeof(void *));
    OTreeValType eval_to = check_binop_compatibility(
            binop_add_mult_sub_eval_to, BINOP_ADD_MULT_SUB_EVAL_TO_LEN,
            left->type, right->type, &swap);
    if (eval_to == OTREE_VAL_INDETERMINATE) {
        fprintf(stderr, "Incompatible types for * operator\n");
        return 1;
    }

    void *new_l_val;
    void *new_r_val;
    OTreeValType new_l_type;
    OTreeValType new_r_type;
    RESOLVE_VAL_SWAP(new_l_val, new_l_type, new_r_val, new_r_type, right, left,
                     swap);

    if (new_l_type == OTREE_VAL_LONG && new_r_type == OTREE_VAL_LONG) {
        *(long *) ret->val = *(long *) new_l_val * *(long *) new_r_val;
    } else if (new_l_type == OTREE_VAL_DOUBLE) {
        *(double *) ret->val = *(double *) new_l_val *
                               (new_r_type == OTREE_VAL_LONG ?
                                ((double) *(long *) new_r_val) :
                                (*(double *) new_r_val));
    } else if (new_l_type == OTREE_VAL_MAT && new_r_type == OTREE_VAL_MAT) {
        ret->val = (void *) matrix_multiply((matrix *) new_l_val,
                                            (matrix *) new_r_val);
    } else {
        ret->val = (void *) matrix_multiply_scalar(
                (matrix *) new_l_val, (float) (
                        new_r_type == OTREE_VAL_LONG ?
                        ((double) *(long *) new_r_val) :
                        (*(double *) new_r_val))
        );
    }

    ret->type = eval_to;
    return 0;
}


int binop_arith_div(OTree *left, OTree *right, OTree *ret) {
    int swap;
    ret->val = malloc(sizeof(void *));
    OTreeValType eval_to = check_binop_compatibility(
            binop_div_eval_to, BINOP_DIV_EVAL_TO_LEN,
            left->type, right->type, &swap);
    if (eval_to == OTREE_VAL_INDETERMINATE) {
        fprintf(stderr, "Incompatible types for / operator\n");
        return 1;
    }

    void *new_l_val;
    void *new_r_val;
    OTreeValType new_l_type;
    OTreeValType new_r_type;
    RESOLVE_VAL_SWAP(new_l_val, new_l_type, new_r_val, new_r_type, right, left,
                     swap);

    if (new_l_type == OTREE_VAL_LONG && new_r_type == OTREE_VAL_LONG) {
        *(long *) ret->val = *(long *) new_l_val / *(long *) new_r_val;
    } else if (new_l_type == OTREE_VAL_MAT) {
        ret->val = (void *) matrix_multiply_scalar(
                (matrix *) new_l_val,
                (float) (1.0 / (new_r_type == OTREE_VAL_LONG ?
                                ((double) *(long *) new_r_val) :
                                (*(double *) new_r_val))));
    } else if (new_l_type == OTREE_VAL_DOUBLE) {
        if (!swap) {
            *(double *) ret->val = *(double *) new_l_val /
                                   (new_r_type == OTREE_VAL_LONG ?
                                    ((double) *(long *) new_r_val) :
                                    (*(double *) new_r_val));
        } else {
            *(double *) ret->val = (new_r_type == OTREE_VAL_LONG ?
                                    ((double) *(long *) new_r_val) :
                                    (*(double *) new_r_val)) /
                                   *(double *) new_l_val;
        }
    } else {
        fprintf(stderr, "Incompatible types for / operator\n");
        return 1;
    }

    ret->type = eval_to;
    return 0;
}

int binop_arith_mod(OTree *left, OTree *right, OTree *ret) {
    if (right->type == OTREE_VAL_LONG && *(long *) right->val == 0) {
        fprintf(stderr, "Divide by zero error\n");
        return 1;
    }
    LOG_AND_BIT_OP_TEMPLATE(left, right, ret, %, "%");
}


int binop_bit_and(OTree *left, OTree *right, OTree *ret) {
    LOG_AND_BIT_OP_TEMPLATE(left, right, ret, &, "&");
}


int binop_bit_xor(OTree *left, OTree *right, OTree *ret) {
    LOG_AND_BIT_OP_TEMPLATE(left, right, ret, ^, "^");
}


int binop_bit_or(OTree *left, OTree *right, OTree *ret) {
    LOG_AND_BIT_OP_TEMPLATE(left, right, ret, |, "|");
}


int binop_log_and(OTree *left, OTree *right, OTree *ret) {
    LOG_AND_BIT_OP_TEMPLATE(left, right, ret, &&, "&&");
}


int binop_log_or(OTree *left, OTree *right, OTree *ret) {
    LOG_AND_BIT_OP_TEMPLATE(left, right, ret, ||, "||");
}


int binop_assmt_equal(OTree *left, OTree *right, OTree *ret) {
    // Assign new variable in the workspace
    HT_KEY_TYPE var_name = (HT_KEY_TYPE) left->val;
    if (HT_get(workspace, var_name, (void *) &ret)) {
        ret = make_empty_otree();
        HT_insert(workspace, var_name, ret);
        HT_insert(var_name_to_str_hash, var_name,
                  format_msg("%s", CTYPE_STR, 1, 1, left->val));
    }

    int recurse_ret = evaluate(right);
    if (recurse_ret) return recurse_ret;

    ret->val = right->val;
    ret->label = right->label;
    ret->type = right->type;
}
