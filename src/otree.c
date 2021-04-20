/* Object tree
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "../include/otree.h"


OTreeLabel get_tree_label_enum(const char *const label) {
    const char *end_label = label;
    size_t end_label_len = strlen(label);
    const char *seek = label;
    while (*seek) {
        if (*seek != '|') {
            seek++;
            continue;
        } else {
            if (strncmp(seek + 1, "char", strlen("char")) == 0 ||
                strncmp(seek + 1, "regex", strlen("regex")) == 0 ||
                strncmp(seek + 1, ">", strlen(">")) == 0) {
                end_label_len = seek - end_label;
                break;
            } else {
                seek++;
                end_label = seek;
            }
        }
    }

    if (strncmp(end_label, "int", end_label_len) == 0) {
        return LM_INT;
    } else if (strncmp(end_label, "float", end_label_len) == 0) {
        return LM_FLOAT;
    } else if (strncmp(end_label, "math_op", end_label_len) == 0) {
        return LM_MATH_OP;
    } else if (strncmp(end_label, "bit_op", end_label_len) == 0) {
        return LM_BIT_OP;
    } else if (strncmp(end_label, "log_op", end_label_len) == 0) {
        return LM_LOGICAL_OP;
    } else if (strncmp(end_label, "allchar", end_label_len) == 0) {
        return LM_ALL_CHARACTERS;
    } else if (strncmp(end_label, "name", end_label_len) == 0) {
        return LM_TOKEN_NAME;
    } else if (strncmp(end_label, "mat_dlm", end_label_len) == 0) {
        return LM_MATRIX_DELIMITER;
    } else if (strncmp(end_label, "assmt", end_label_len) == 0) {
        return LM_ASSIGNMENT_OP;
    } else if (strncmp(end_label, "al_dlm", end_label_len) == 0) {
        return LM_ARGUMENT_LIST_DELIMITER;
    } else if (strncmp(end_label, "num", end_label_len) == 0) {
        return LM_ANY_NUMBER;
    } else if (strncmp(end_label, "str_lit", end_label_len) == 0) {
        return LM_STRING_LITERAL;
    } else if (strncmp(end_label, "mat_lit", end_label_len) == 0) {
        return LM_MATRIX_LITERAL;
    } else if (strncmp(end_label, "smpexpr", end_label_len) == 0) {
        return LM_SIMPLE_EXPRESSION;
    } else if (strncmp(end_label, "", end_label_len) == 0) {
        return LM_ARGUMENT_LIST;
    } else if (strncmp(end_label, "fexpr", end_label_len) == 0) {
        return LM_FUNCTION_CALL_EXPRESSION;
    } else if (strncmp(end_label, "anyexpr", end_label_len) == 0) {
        return LM_ANY_EXPRESSION;
    } else if (strncmp(end_label, "type", end_label_len) == 0) {
        return LM_TYPE;
    } else if (strncmp(end_label, "varname", end_label_len) == 0) {
        return LM_VARNAME;
    } else if (strncmp(end_label, "a_stmt", end_label_len) == 0) {
        return LM_STATEMENT_ASSIGNMENT;
    } else if (strncmp(end_label, "stmt", end_label_len) == 0) {
        return LM_STATEMENT;
    } else if (strncmp(end_label, ">", end_label_len) == 0) {
        return LM_LAB_MAT;
    } else {
        return LM_NO_LABEL;
    }
}


int otree_parse_atomic(const char *const contents, OTree *const otree) {
    switch (otree->label) {
        case LM_INT:
            return _otree_parse_atomic_int(contents, otree);
        case LM_FLOAT:
            return _otree_parse_atomic_float(contents, otree);
        case LM_ASSIGNMENT_OP:
        case LM_MATH_OP:
        case LM_BIT_OP:
        case LM_LOGICAL_OP:
        case LM_ALL_CHARACTERS:
        case LM_TOKEN_NAME:
        case LM_MATRIX_DELIMITER:
        case LM_ARGUMENT_LIST_DELIMITER:
            fprintf(stderr, "unhandled case in otree_parse_atomic\n");
            return 1;
        default:
            fprintf(stderr, "otree_parse_atomic invoked with non-atomic "
                            "label\n");
            return 1;
    }
}


int _otree_parse_atomic_int(const char *const contents, OTree *const otree) {
    char *endptr;
    long str_as_l = strtol(contents, &endptr, 10);
    if (errno == ERANGE) {
        char *err_msg_template = ERR_MSG_INT_OVERUNDERFLOW(contents);
        char *err_msg = ERR_MSG_STATIC(err_msg_template);
        fprintf(stderr, "%s\n", err_msg);
        free(err_msg_template);
        free(err_msg);
        return 1;
    }

    long *val_ptr = malloc(sizeof(double));
    *val_ptr = str_as_l;
    otree->val = (void *) val_ptr;
    return 0;
}


int _otree_parse_atomic_float(const char *const contents, OTree *const otree) {
    char *endptr;
    double str_as_d = strtod(contents, &endptr);
    if (errno == ERANGE) {
        char *err_msg_template = ERR_MSG_FLOAT_OVERUNDERFLOW(contents);
        char *err_msg = ERR_MSG_STATIC(err_msg_template);
        fprintf(stderr, "%s\n", err_msg);
        free(err_msg_template);
        free(err_msg);
        return 1;
    }

    double *val_ptr = malloc(sizeof(double));
    *val_ptr = str_as_d;
    otree->val = (void *) val_ptr;
    return 0;
}


int otree_parse_literal(const char *const contents, OTree *const otree) {
    switch (otree->label) {
        case LM_ANY_NUMBER:
            if (strstr(contents, ".")) {
                otree->label = LM_FLOAT;
                return _otree_parse_atomic_float(contents, otree);
            } else {
                otree->label = LM_INT;
                return _otree_parse_atomic_int(contents, otree);
            }
        case LM_STRING_LITERAL:
            // Format msg takes care of allocation of memory to copy the
            // contents string into a new memory chunk.
            otree->val = format_msg("%s", CTYPE_STR, 1, contents);
            return 0;
        case LM_MATRIX_LITERAL:
            fprintf(stderr, "unhandled case in otree_parse_atomic\n");
            return 1;
        default:
            fprintf(stderr, "otree_parse_atomic invoked with non-atomic "
                            "label\n");
            return 1;
    }
}


int otree_parse_name(const char *const contents, OTree *const otree) {
    switch (otree->label) {
        case LM_VARNAME:
        case LM_TYPE:
            otree->val = format_msg("%s", CTYPE_STR, 1, contents);
            return 0;
        default:
            fprintf(stderr, "otree_parse_name invoked with non-atomic "
                            "label");
            return 1;
    }
}


OTree *make_empty_otree() {
    OTree *otree = malloc(sizeof(OTree));
    otree->val = NULL;
    otree->label = LM_NO_LABEL;
    otree->children = NULL;
}


OTree *ast_2_otree(const mpc_ast_t *const ast, int *status) {
    OTree *otree = make_empty_otree();
    otree->label = get_tree_label_enum(ast->tag);;

    switch (otree->label) {
        case LM_INT:
        case LM_FLOAT:
        case LM_MATH_OP:
        case LM_BIT_OP:
        case LM_LOGICAL_OP:
        case LM_ALL_CHARACTERS:
        case LM_TOKEN_NAME:
        case LM_MATRIX_DELIMITER:
        case LM_ASSIGNMENT_OP:
        case LM_ARGUMENT_LIST_DELIMITER:
            *status |= otree_parse_atomic(ast->contents, otree);
            return otree;
        case LM_ANY_NUMBER:
        case LM_STRING_LITERAL:
        case LM_MATRIX_LITERAL:
            *status |= otree_parse_literal(ast->contents, otree);
            return otree;
        case LM_VARNAME:
        case LM_TYPE:
            *status |= otree_parse_name(ast->contents, otree);
            return otree;
        case LM_NO_LABEL:
            *status |= 1;
            fprintf(stderr, "%s", "abstract syntax tree node encountered with "
                                  "the LM_NO_LABEL label\n");
            return otree;
        default:
            break;
    }

    otree->children = SLL_create();
    SLL_Node *prev = otree->children->head;
    for (int i = 0; i < ast->children_num; i++) {
        if ((strcmp(ast->children[i]->contents, "(") == 0) ||
            (strcmp(ast->children[i]->contents, ")") == 0) ||
            (strcmp(ast->children[i]->contents, "'") == 0) ||
            (strcmp(ast->children[i]->tag, "string") == 0) ||
            (strcmp(ast->children[i]->tag, "regex") == 0))
            continue;
        prev = SLL_insert_after(otree->children,
                                ast_2_otree(ast->children[i], status),
                                prev);
    }
    return otree;
}
