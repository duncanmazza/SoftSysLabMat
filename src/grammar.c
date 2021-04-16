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

    mpc_parser_t *Log_op = mpc_new("log_op");
    all_parsers[5] = Log_op;

    mpc_parser_t *Expr = mpc_new("expr");
    all_parsers[4] = Expr;

    mpc_parser_t *Lab_mat = mpc_new("lab_mat");
    all_parsers[5] = Lab_mat;

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT, "\
        int     : /-?[0-9]+/ ;\
        float   : /-?([0-9]*[.])[0-9]+/ ;\
        math_op : '+' | '-' | '*' | '/' | '%' ;\
        bit_op  : '&' | '^' | '|' ;\
        log_op  : \"&&\" | \"||\" ;\
        expr    : (<float>|<int>) <math_op> (<float>|<int>) | <int> <bit_op> <int> | <int> <log_op> <int> ;\
        lab_mat : /^/ <expr>* /$/ ;\
        ", Int, Float, Math_op, Bit_op, Log_op, Expr, Lab_mat);
    return Lab_mat;
}
