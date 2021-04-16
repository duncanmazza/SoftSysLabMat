//
// Created by duncan on 4/15/21.
//

#include "../include/grammar.h"


mpc_parser_t *mpc_setup(mpc_parser_t **all_parsers) {
    mpc_parser_t *Int = mpc_new("int");
    all_parsers[0] = Int;

    mpc_parser_t *Float = mpc_new("float");
    all_parsers[0] = Float;

    mpc_parser_t *Math_op = mpc_new("math_op");
    all_parsers[1] = Math_op;

    mpc_parser_t *Bit_op = mpc_new("bit_op");
    all_parsers[2] = Bit_op;

    mpc_parser_t *Qexpr = mpc_new("qexpr");
    all_parsers[3] = Qexpr;

    mpc_parser_t *Expr = mpc_new("expr");
    all_parsers[4] = Expr;

    mpc_parser_t *lab_mat = mpc_new("lab_mat");
    all_parsers[5] = lab_mat;

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT, "\
        int     : /-?[0-9]+/ ;\
        float   : /-?([0-9]*[.])[0-9]+/ ;\
        math_op : '+' | '-' | '*' | '/' | '%' ;\
        bit_op  : '&' | '^' | '|' ;\
        expr    : (<float> | <int>) <math_op> (<float> | <int>) | <int> <bit_op> <int> ;\
        lab_mat : /^/ <expr>* /$/ ;\
        ", Int, Float, Math_op, Bit_op, Expr, lab_mat);
    return lab_mat;
}
