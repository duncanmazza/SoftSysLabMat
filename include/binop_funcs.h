/* Binary operator evaluation functions
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_BINOP_FUNCS_H
#define SOFTSYSSOFTSYSLABMAT_BINOP_FUNCS_H

#include "otree.h"
#include "matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int (*binop_func_ptrs[])(OTree *, OTree*);

#define RESOLVE_VAL_SWAP(new_l_val, new_l_type, new_r_val, new_r_type, right,  \
left, swap) ({                                                                 \
    (new_l_val) = (swap) ? (right)->val : (left)->val;                         \
    (new_l_type) = (swap) ? (right)->type : (left)->type;                      \
    (new_r_val) = (swap) ? (left)->val : (right)->val;                         \
    (new_r_type) = (swap) ? (left)->type : (right)->type;                      \
})


int binop_arith_add(OTree *left, OTree *right);

int binop_arith_mult(OTree *left, OTree *right);

int binop_arith_div(OTree *left, OTree *right);

int binop_arith_mod(OTree *left, OTree *right);

int binop_bit_and(OTree *left, OTree *right);

int binop_bit_xor(OTree *left, OTree *right);

int binop_bit_or(OTree *left, OTree *right);

int binop_log_and(OTree *left, OTree *right);

int binop_log_or(OTree *left, OTree *right);

int binop_assmt_equal(OTree *left, OTree *right);

#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_BINOP_FUNCS_H
