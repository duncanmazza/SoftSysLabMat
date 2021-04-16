//
// Created by duncan on 4/15/21.
//

#include "../include/grammar.h"


mpc_parser_t *mpc_setup(mpc_parser_t **all_parsers) {
    mpc_parser_t *Int = mpc_new("int");
    all_parsers[0] = Int;

    mpc_parser_t *Float = mpc_new("float");
    all_parsers[1] = Float;

    mpc_parser_t *mth_op = mpc_new("mth_op");
    all_parsers[2] = mth_op;

    mpc_parser_t *Bit_op = mpc_new("bit_op");
    all_parsers[3] = Bit_op;

    mpc_parser_t *Log_op = mpc_new("log_op");
    all_parsers[4] = Log_op;

    mpc_parser_t *Var = mpc_new("var");
    all_parsers[5] = Var;

    mpc_parser_t *Statement = mpc_new("stmt");
    all_parsers[6] = Statement;

    mpc_parser_t *Expr = mpc_new("expr");
    all_parsers[7] = Expr;

    mpc_parser_t *Assignment = mpc_new("asmt");
    all_parsers[8] = Assignment;

    mpc_parser_t *Lab_mat = mpc_new("lab_mat");
    all_parsers[9] = Lab_mat;

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
        "int     : /-?[0-9]+/ ;"
        "float   : /-?([0-9]*[.])[0-9]+/ ;"
        "mth_op  : '+' | '-' | '*' | '/' | '%' ;"
        "bit_op  : '&' | '^' | '|' ;"
        "log_op  : \"&&\" | \"||\" ;"
        "expr    : (<float>|<int>) <mth_op> (<float>|<int>) "
        "        | <int> <bit_op> <int> | <int> <log_op> <int> ;"
        "var     : /[a-zA-Z_][a-zA-Z0-9_]*/ ;"
        "asmt    : '=' ;"
        "stmt    : <var> <asmt> <expr> ;"
        "lab_mat : /^/ <stmt> /$/ ;", Int, Float, mth_op, Bit_op, Log_op, Expr,
        Var, Assignment, Statement, Lab_mat);
    return Lab_mat;
}
