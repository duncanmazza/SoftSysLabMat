/* Object tree
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_OTREE_H
#define SOFTSYSSOFTSYSLABMAT_OTREE_H

#include "sll.h"
#include "dll.h"
#include "str_utils.h"
#include "matrix.h"
#include "../lib/mpc/mpc.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_MSG_STATIC(msg) format_msg("STATIC_PARSING_ERR: %s", CTYPE_STR, 0, 1, \
    (msg))
#define ERR_MSG_FLOAT_OVERUNDERFLOW(culprit) format_msg("Could not parse %s "  \
    "as an double due to over/underflow", CTYPE_STR, 0, 1, (culprit))
#define ERR_MSG_INT_OVERUNDERFLOW(culprit) format_msg("Could not parse %s as " \
    "a long due to over/underflow", CTYPE_STR, 0, 1, (culprit))


extern const char *const get_tree_label_enum_ignore_arr[];
extern const size_t get_tree_label_enum_ignore_arr_strlen[];


typedef enum {
    LM_NO_LABEL,
    LM_CHAR,
    LM_STATEMENT,
    LM_STATEMENT_ASSIGNMENT,
    LM_ANY_EXPRESSION,
    LM_EXPRESSION,
    LM_FUNCTION_CALL_EXPRESSION,
    LM_SIMPLE_EXPRESSION,
    LM_MATRIX_LITERAL,
    LM_STRING_LITERAL,
    LM_ANY_NUMBER,
    LM_ARGUMENT_LIST_DELIMITER,
    LM_ASSIGNMENT_OP,
    LM_MATRIX_COMMA_DELIMITER,
    LM_MATRIX_SEMICOLON_DELIMITER,
    LM_TOKEN_NAME,
    LM_ALL_CHARACTERS,
    LM_LOGICAL_OP,
    LM_BIT_OP,
    LM_MATH_OP,
    LM_FLOAT,
    LM_INT,
    LM_ARGUMENT_LIST,
    LM_LAB_MAT,
} OTreeLabel;
#define NUM_OTREE_LABELS (LM_LAB_MAT + 1)
extern const char *const otree_label_strs[];
extern const char *const otree_rule_strs[];


typedef enum {
    OTREE_VAL_INDETERMINATE,
    OTREE_VAL_STR,
    OTREE_VAL_LONG,
    OTREE_VAL_DOUBLE,
    OTREE_VAL_PARENT,
    OTREE_VAL_MAT,
    OTREE_VAL_BINOP_ENUM,
    OTREE_VAL_DELIM,
} OTreeValType;
extern const char* const otree_val_type_enum_strs[];

typedef struct {
    OTreeValType arg1;
    OTreeValType arg2;
    OTreeValType ret_val;
} OTreeValTypeTrio;


typedef struct {
    OTreeLabel label;
    OTreeValType type;
    void *val;
    DLL *children;
} OTree;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
typedef enum {
    BINOP_ARITH_ADD,
    BINOP_ARITH_SUB,
    BINOP_ARITH_MULT,
    BINOP_ARITH_DIV,
    BINOP_ARITH_MOD,

    BINOP_BIT_AND,
    BINOP_BIT_XOR,
    BINOP_BIT_OR,

    BINOP_LOG_AND,
    BINOP_LOG_OR,

    BINOP_ASSMT_EQUAL,
} OPEnum;
#pragma clang diagnostic pop
extern const char *const binop_enum_strs[];
#define NUM_OPS (BINOP_ASSMT_EQUAL + 1)

extern const OTreeValTypeTrio binop_add_mult_sub_eval_to[];
#define BINOP_ADD_MULT_SUB_EVAL_TO_LEN 6

extern const OTreeValTypeTrio binop_div_eval_to[];
#define BINOP_DIV_EVAL_TO_LEN 5


#define INDENT_SZ 2


OTree *ast_2_otree(const mpc_ast_t *ast, int *status);

OTreeLabel get_tree_label_enum(const char *label);

/** Parse mpc abstract syntax tree node label string by extracting the last
 * label.
 *
 * mpc label strings look something like "num|int|regex". This function modifies
 * the string pointed to by *end_label such that the last label in this list
 * (where the delimiter is '|') is pointed to that is not in the ignore_str_len
 * array. For example, specifying that "regex" should be ignored should result
 * in *end_label = "int|regex"; the return value would be 3 to specify the
 * length of the "int" label.
 *
 * @param ignore Array labels to ignore at the end of the label string.
 * @param ignore_len Length of the ignore array
 * @param ignore_str_len Array corresponding to the lengths of the strings in
 *                       ignore
 * @param end_label Pointer to the character pointer of the label string
 * @return Length of the label pointed to by *end_label
 */
size_t
get_mpc_end_label_ignore(const char *const *ignore, size_t ignore_len,
                         const size_t *ignore_str_len,
                         const char **end_label);

int otree_atomic_parse_float(const char *contents, OTree *otree);

int otree_parse_atomic(const char *contents, OTree *otree);

int otree_atomic_parse_int(const char *contents, OTree *otree);

OTree *make_empty_otree();

int otree_construct_matrix(const mpc_ast_t *ast, OTree *otree);

int otree_parse_literal(const mpc_ast_t *ast, OTree *otree);

int otree_atomic_parse_op(const char *symb, OTree *otree);

void disp_otree_recursive(const OTree *otree, DLL *repr_dll, size_t indent);

void print_otree(const OTree *otree);

void child_replace_current(DLL_Node *child, OTree *current);


#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_OTREE_H
