/* Binary operator evaluation functions
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_BINOP_FUNCS_H
#define SOFTSYSSOFTSYSLABMAT_BINOP_FUNCS_H

#include "otree.h"
#include "matrix.h"
#include "ht.h"
#include "evaluate.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int (*binop_func_ptrs[])(OTree *, OTree *, OTree *);

#define RESOLVE_VAL_SWAP(new_l_val, new_l_type, new_r_val, new_r_type, right,  \
left, swap) ({                                                                 \
    (new_l_val) = (swap) ? (right)->val : (left)->val;                         \
    (new_l_type) = (swap) ? (right)->type : (left)->type;                      \
    (new_r_val) = (swap) ? (left)->val : (right)->val;                         \
    (new_r_type) = (swap) ? (left)->type : (right)->type;                      \
})


#define LOG_AND_BIT_OP_TEMPLATE(left, right, ret, op, op_str) ({               \
    (ret)->val = malloc(sizeof(void *));                                       \
    if ((left)->type == OTREE_VAL_LONG && (right)->type == OTREE_VAL_LONG) {   \
        *(long *) (ret)->val = (*(long *) (left)->val) op                      \
                               (*(long *) (right)->val);                       \
        (ret)->type = OTREE_VAL_LONG;                                          \
    } else {                                                                   \
        fprintf(stderr, "Incompatible types for %s operator\n", (op_str));     \
        return 1;                                                              \
    }                                                                          \
    return 0;})

int binop_arith_add(OTree *left, OTree *right, OTree *ret);

int binop_arith_sub(OTree *left, OTree *right, OTree *ret);

int binop_arith_mult(OTree *left, OTree *right, OTree *ret);

int binop_arith_div(OTree *left, OTree *right, OTree *ret);

int binop_arith_mod(OTree *left, OTree *right, OTree *ret);

int binop_bit_and(OTree *left, OTree *right, OTree *ret);

int binop_bit_xor(OTree *left, OTree *right, OTree *ret);

int binop_bit_or(OTree *left, OTree *right, OTree *ret);

int binop_log_and(OTree *left, OTree *right, OTree *ret);

int binop_log_or(OTree *left, OTree *right, OTree *ret);

int binop_assmt_equal(OTree *left, OTree *right, OTree *ret);

#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_BINOP_FUNCS_H
