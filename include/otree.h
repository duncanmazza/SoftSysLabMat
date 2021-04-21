/* Object tree
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_OTREE_H
#define SOFTSYSSOFTSYSLABMAT_OTREE_H

#include "sll.h"
#include "../lib/mpc/mpc.h"
#include <string.h>
#include "format_msg.h"


#define ERR_MSG_STATIC(msg) format_msg("STATIC_PARSING_ERR: %s", CTYPE_STR, 1, \
    (msg))
#define ERR_MSG_FLOAT_OVERUNDERFLOW(culprit) format_msg("Could not parse %s "  \
    "as an double due to over/underflow", CTYPE_STR, 1, (culprit))
#define ERR_MSG_INT_OVERUNDERFLOW(culprit) format_msg("Could not parse %s as " \
    "a long due to over/underflow", CTYPE_STR, 1, (culprit))


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LM_NO_LABEL,
    LM_CHAR,
    LM_STATEMENT,
    LM_STATEMENT_ASSIGNMENT,
    LM_TYPE,
    LM_VARNAME,
    LM_ANY_EXPRESSION,
    LM_FUNCTION_CALL_EXPRESSION,
    LM_SIMPLE_EXPRESSION,
    LM_MATRIX_LITERAL,
    LM_STRING_LITERAL,
    LM_ANY_NUMBER,
    LM_ARGUMENT_LIST_DELIMITER,
    LM_ASSIGNMENT_OP,
    LM_MATRIX_DELIMITER,
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

typedef struct {
    OTreeLabel label;
    void *val;
    SLL *children;
} OTree;


typedef enum {
    OP_ARITHMETIC_ADD,
    OP_ARITHMETIC_SUB,
    OP_ARITHMETIC_MULT,
    OP_ARITHMETIC_DIV,
    OP_ARITHMETIC_MOD,

    OP_BIT_AND,
    OP_BIT_XOR,
    OP_BIT_OR,

    OP_LOG_AND,
    OP_LOG_OR,

    OP_ASSIGNMENT,
} OP_Enum;

#define NUM_OPS OP_ASSIGNMENT + 1

extern const char* const op_enum_strs[];


OTree *ast_2_otree(const mpc_ast_t *const ast, int *status);

OTreeLabel get_tree_label_enum(const char *const label);

int _otree_atomic_parse_float(const char *const contents, OTree *const otree);

int otree_parse_atomic(const char *const contents, OTree *const otree);

int _otree_atomic_parse_int(const char *const contents, OTree *const otree);

OTree *make_empty_otree();

int otree_parse_literal(const mpc_ast_t *const ast, OTree *const otree);

int otree_parse_name(const char *const contents, OTree *const otree);

int _otree_atomic_parse_op(const char* const symb, OTree *const otree);

#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_OTREE_H
