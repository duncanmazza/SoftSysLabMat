/* Binary operator evaluation functions
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "../include/binop_funcs.h"

// This must correspond exactly to the order as prescribed in OP_Enum
int (*binop_func_ptrs[])(OTree *, OTree*) = {
        binop_arith_add,
        binop_arith_mult,
        binop_arith_div,
        binop_arith_mod,
        binop_bit_and,
        binop_bit_xor,
        binop_bit_or,
        binop_log_and,
        binop_log_or,
        binop_assmt,
};


int binop_arith_add(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: +");
    return 1;
}


int binop_arith_mult(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: *");
    return 1;
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


int binop_assmt(OTree *left, OTree *right) {
    fprintf(stderr, "Un-implemented operator evaluation: =");
    return 1;
}
