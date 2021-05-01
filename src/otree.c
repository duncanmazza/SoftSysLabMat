/* Object tree
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include <dll.h>
#include "../include/otree.h"

/* This must correspond exactly to the order as prescribed in the OP_Enum
 * enum */
const char *const op_enum_strs[] = {
        "+", "-", "*", "/", "%",
        "&", "^", "|",
        "&&", "||",
        "=",
};


const char *const get_tree_label_enum_ignore_arr[4] = {"char", "regex",
                                                       "string", ">"};
const size_t get_tree_label_enum_ignore_arr_strlen[4] = {4, 5, 6, 1};


/* This must correspond exactly to the order as prescribed in the OTreeLabel
 * enum */
const char *const otree_label_strs[] = {
        "LM_NO_LABEL",
        "LM_CHAR",
        "LM_STATEMENT",
        "LM_STATEMENT_ASSIGNMENT",
        "LM_ANY_EXPRESSION",
        "LM_EXPRESSION",
        "LM_FUNCTION_CALL_EXPRESSION",
        "LM_SIMPLE_EXPRESSION",
        "LM_MATRIX_LITERAL",
        "LM_STRING_LITERAL",
        "LM_ANY_NUMBER",
        "LM_ARGUMENT_LIST_DELIMITER",
        "LM_ASSIGNMENT_OP",
        "LM_MATRIX_COMMA_DELIMITER",
        "LM_MATRIX_SEMICOLON_DELIMITER",
        "LM_TOKEN_NAME",
        "LM_ALL_CHARACTERS",
        "LM_LOGICAL_OP",
        "LM_BIT_OP",
        "LM_MATH_OP",
        "LM_FLOAT",
        "LM_INT",
        "LM_ARGUMENT_LIST",
        "LM_LAB_MAT",
};


/* This must correspond exactly to the order as prescribed in the OTreeLabel
 * enum */
const char *const otree_rule_strs[] = {
        "",  // LM_NO_LABEL
        "char",
        "stmt",
        "a_stmt",
        "anyexpr",
        "expr",
        "fexpr",
        "smpexpr",
        "mat_lit",
        "str_lit",
        "num",
        "al_dlm",
        "assmt",
        "matcdlm",
        "matsdlm",
        "name",
        "all_char",
        "log_op",
        "bit_op",
        "math_op",
        "float",
        "int",
        "arglist",
        ">",  // LM_LAB_MAT
};

size_t
_get_mpc_end_label_ignore(const char *const *ignore, const size_t ignore_len,
                          const size_t *ignore_str_len,
                          const char **end_label) {
    size_t end_label_len = strlen(*end_label);
    const char *seek = *end_label;
    while (*seek) {
        if (*seek != '|') {
            seek++;
            continue;
        } else {
            int encountered_ignore = 0;
            for (int i = 0; i < ignore_len; i++) {
                encountered_ignore |= strncmp(seek + 1, ignore[i],
                                              ignore_str_len[i]) == 0;
            }
            if (encountered_ignore) {
                end_label_len = seek - *end_label;
                return end_label_len;
            } else {
                seek++;
                *end_label = seek;
            }
        }
    }
    return end_label_len;
}


OTreeLabel get_tree_label_enum(const char *const label) {
    const char *end_label = label;
    size_t end_label_len = \
        _get_mpc_end_label_ignore(get_tree_label_enum_ignore_arr, 4,
                                  get_tree_label_enum_ignore_arr_strlen,
                                  &end_label);

    for (int i = 0; i < NUM_OTREE_LABELS; i++) {
        if (strncmp(end_label, otree_rule_strs[i], end_label_len) == 0)
            return (OTreeLabel) i;
    }
    return LM_NO_LABEL;
}


int otree_parse_atomic(const char *const contents, OTree *const otree) {
    switch (otree->label) {
        case LM_INT:
            return _otree_atomic_parse_int(contents, otree);
        case LM_FLOAT:
            return _otree_atomic_parse_float(contents, otree);
        case LM_ASSIGNMENT_OP:
        case LM_MATH_OP:
        case LM_BIT_OP:
        case LM_LOGICAL_OP:
            return _otree_atomic_parse_op(contents, otree);
        case LM_TOKEN_NAME:
        case LM_ALL_CHARACTERS:
            otree->val = format_msg("%s", CTYPE_STR, 0, 1, contents);
            return 0;
        case LM_ARGUMENT_LIST_DELIMITER:
        case LM_MATRIX_COMMA_DELIMITER:
            otree->val = format_msg("%s", CTYPE_STR, 0, 1, ",");
            return 0;
        case LM_MATRIX_SEMICOLON_DELIMITER:
            otree->val = format_msg("%s", CTYPE_STR, 0, 1, ";");
            return 0;
        default:
            fprintf(stderr, "otree_parse_atomic invoked with non-atomic "
                            "label\n");
            return 1;
    }
}


int _otree_atomic_parse_int(const char *const contents, OTree *const otree) {
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


int _otree_atomic_parse_float(const char *const contents, OTree *const otree) {
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


int _otree_atomic_parse_op(const char *const symb, OTree *const otree) {
    size_t symb_strlen = strlen(symb);
    for (int i = 0; i < NUM_OPS; i++) {
        if (strncmp(op_enum_strs[i], symb, symb_strlen) != 0) continue;
        OP_Enum *op_alloc = malloc(sizeof(OP_Enum));
        *op_alloc = (OP_Enum) i;
        otree->val = op_alloc;
        return 0;
    }
    fprintf(stderr, "unhandled case encountered when parsing an operator\n");
    return 1;
}


int _otree_construct_matrix(const mpc_ast_t *const ast, OTree *const otree) {
    size_t rows = 0;
    size_t columns_check = 1;
    size_t columns = 1;
    OTreeLabel ast_label_record[ast->children_num];
    for (int i = 0; i < ast->children_num; i++) {
        OTreeLabel label = get_tree_label_enum(ast->children[i]->tag);
        ast_label_record[i] = label;
        if (label == LM_MATRIX_COMMA_DELIMITER) {
            columns_check++;
        } else if (label == LM_MATRIX_SEMICOLON_DELIMITER) {
            rows++;
            if (columns != 1 && columns_check != columns) {
                fprintf(stderr, "Inconsistent columns given in the "
                                "matrix literal");
                return 1;
            }
            columns = columns_check;
            if (strncmp(ast->children[i + 2]->contents, "]", 1) != 0)
                columns_check = 1;
        } else if (label == LM_CHAR) {
            if (strncmp(ast->children[i]->contents, "]", 1) == 0) {
                if (columns != 1 && columns_check != columns) {
                    fprintf(stderr, "Inconsistent columns given in the "
                                    "matrix literal\n");
                    return 1;
                }
                if (!(ast_label_record[i - 2] == LM_MATRIX_COMMA_DELIMITER ||
                    ast_label_record[i - 2] == LM_MATRIX_SEMICOLON_DELIMITER)) {
                    rows++;
                }
                break;
            }
        }
    }
    columns = columns_check;

    float input[rows * columns];
    size_t input_counter = 0;
    for (int i = 0; i < ast->children_num; i++) {
        OTreeLabel label = ast_label_record[i];
        char *endptr;
        if (label == LM_FLOAT) {
            double str_as_d = strtod(ast->children[i]->contents, &endptr);
            if (errno == ERANGE) {
                char *err_msg_template = ERR_MSG_FLOAT_OVERUNDERFLOW(
                        ast->children[i]->contents);
                char *err_msg = ERR_MSG_STATIC(err_msg_template);
                fprintf(stderr, "%s\n", err_msg);
                free(err_msg_template);
                free(err_msg);
                return 1;
            }
            input[input_counter++] = (float) str_as_d;
        } else if (label == LM_INT) {
            long str_as_l = strtol(ast->children[i]->contents, &endptr, 10);
            if (errno == ERANGE) {
                char *err_msg_template = ERR_MSG_INT_OVERUNDERFLOW(
                        ast->children[i]->contents);
                char *err_msg = ERR_MSG_STATIC(err_msg_template);
                fprintf(stderr, "%s\n", err_msg);
                free(err_msg_template);
                free(err_msg);
                return 1;
            }
            input[input_counter++] = (float) str_as_l;
        } else {
            continue;
        }
    }

    matrix* mat = make_matrix((int)rows, (int)columns);
    if (complete_matrix(mat, input, (int)rows, (int)columns) == 0) return 1;
    otree->val = mat;
    return 0;
}

int otree_parse_literal(const mpc_ast_t *const ast, OTree *const otree) {
    switch (otree->label) {
        case LM_ANY_NUMBER:
            if (strstr(ast->contents, ".")) {
                otree->label = LM_FLOAT;
                return _otree_atomic_parse_float(ast->contents, otree);
            } else {
                otree->label = LM_INT;
                return _otree_atomic_parse_int(ast->contents, otree);
            }
        case LM_STRING_LITERAL:
            // Format msg takes care of allocation of memory to copy the
            // contents string into a new memory chunk.
            otree->val = format_msg("%s", CTYPE_STR, 0, 1,
                                    ast->children[1]->contents);
            return 0;
        case LM_MATRIX_LITERAL:
            return _otree_construct_matrix(ast, otree);
        default:
            fprintf(stderr, "otree_parse_atomic invoked with non-atomic "
                            "label\n");
            return 1;
    }
}


OTree *make_empty_otree() {
    OTree *otree = malloc(sizeof(OTree));
    otree->val = NULL;
    otree->label = LM_NO_LABEL;
    otree->children = NULL;
}


OTreeValType otree_classify_val(const OTree *const otree) {
    switch (otree->label) {
        case LM_NO_LABEL:
        case LM_CHAR:
        case LM_ANY_NUMBER:
        case LM_ALL_CHARACTERS:
            return OTREE_SHOULD_NOT_EXIST;
        case LM_STATEMENT:
        case LM_STATEMENT_ASSIGNMENT:
        case LM_ANY_EXPRESSION:
        case LM_EXPRESSION:
        case LM_FUNCTION_CALL_EXPRESSION:
        case LM_SIMPLE_EXPRESSION:
        case LM_ARGUMENT_LIST:
        case LM_LAB_MAT:
            return OTREE_VAL_SLL;
        case LM_STRING_LITERAL:
        case LM_TOKEN_NAME:
            return OTREE_VAL_STR;
        case LM_ASSIGNMENT_OP:
        case LM_LOGICAL_OP:
        case LM_BIT_OP:
        case LM_MATH_OP:
            return OTREE_VAL_OP_ENUM;
        case LM_MATRIX_LITERAL:
            return OTREE_VAL_MAT;
        case LM_MATRIX_COMMA_DELIMITER:
        case LM_ARGUMENT_LIST_DELIMITER:
            return OTREE_DELIM;
        case LM_FLOAT:
            return OTREE_VAL_DOUBLE;
        case LM_INT:
            return OTREE_VAL_LONG;
        default:
            fprintf(stderr, "Unhandled case in OTree type classification");
            exit(-1);
    }
}


void disp_otree(const OTree *const otree) {
    DLL *disp_dll = DLL_create();
    _disp_otree(otree, disp_dll, 0);
    SLL *disp_sll = DLL_to_SLL(disp_dll);
    char *disp_str = sll_strs_to_str(disp_sll, "\n", "\n");
    printf("%s", disp_str);
    SLL_clean(disp_sll);
    free(disp_dll);  // disp_sll is a shallow copy so this is sufficient
    free(disp_str);
}


void _disp_otree(const OTree *const otree, DLL *const repr_dll, size_t indent) {
    size_t this_indent_sz = indent;
    char *indent_str = malloc(this_indent_sz + 3);
    memset(indent_str, ' ', this_indent_sz);
    indent_str[this_indent_sz] = '>';
    indent_str[this_indent_sz + 1] = ' ';
    indent_str[this_indent_sz + 2] = '\0';

    if (otree->children) {
        size_t new_indent = indent + INDENT_SZ;
        SLL_Node *node = otree->children->head;

        const char *disp = otree_label_strs[otree->label];
        char *concatenated = malloc(strlen(disp) + strlen(indent_str) + 1);
        strcpy(concatenated, indent_str);
        strcat(concatenated, disp);
        DLL_append(repr_dll, concatenated);

        while (node) {
            _disp_otree((OTree *) node->val, repr_dll, new_indent);
            node = node->next;
        }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointers"
        free(indent_str);
#pragma clang diagnostic pop
        return;
    }

    char *value_disp;
    char *mat_repr;
    OTreeValType classification = otree_classify_val(otree);
    switch (classification) {
        case OTREE_DELIM:
        case OTREE_VAL_STR:
            value_disp = QUICK_MSG((char *) otree->val);
            break;
        case OTREE_VAL_LONG:
            value_disp = format_msg(ctype_str_formatting[CTYPE_LONG],
                                    CTYPE_LONG, 0, 1, *(long *) otree->val);
            break;
        case OTREE_VAL_DOUBLE:
            value_disp = format_msg(ctype_str_formatting[CTYPE_DOUBLE],
                                    CTYPE_DOUBLE, 0, 1, *(long *) otree->val);
            break;
        case OTREE_VAL_MAT:
            mat_repr = matrix_str_repr((matrix *)otree->val);
            value_disp = format_msg("Matrix: \n%s", CTYPE_STR, 0, 1, mat_repr);
            free(mat_repr);
            break;
        case OTREE_VAL_OP_ENUM:
            value_disp = QUICK_MSG(op_enum_strs[*(OP_Enum *) otree->val]);
            break;
        case OTREE_VAL_SLL:
            fprintf(stderr,
                    "Contradiction: OTree object classified as containing "
                    "a SLL but was found to a null children field");
            exit(-1);
        case OTREE_SHOULD_NOT_EXIST:
            fprintf(stderr,
                    "Encountered OTree object that should not have been created");
            exit(-1);
        default:
            fprintf(stderr, "_disp_otree unhandled case");
            exit(-1);
    }

    char *concatenated = malloc(strlen(value_disp) + strlen(indent_str) + 1);
    strcpy(concatenated, indent_str);
    strcat(concatenated, value_disp);
    free(value_disp);
    free(indent_str);
    DLL_append(repr_dll, concatenated);
}


OTree *ast_2_otree(const mpc_ast_t *const ast, int *status) {
    OTree *otree = make_empty_otree();
    otree->label = get_tree_label_enum(ast->tag);

    switch (otree->label) {
        case LM_INT:
        case LM_FLOAT:
        case LM_MATH_OP:
        case LM_BIT_OP:
        case LM_LOGICAL_OP:
        case LM_ALL_CHARACTERS:
        case LM_TOKEN_NAME:
        case LM_ASSIGNMENT_OP:
        case LM_MATRIX_COMMA_DELIMITER:
        case LM_MATRIX_SEMICOLON_DELIMITER:
        case LM_ARGUMENT_LIST_DELIMITER:
            *status |= otree_parse_atomic(ast->contents, otree);
            return otree;
        case LM_ANY_NUMBER:
        case LM_STRING_LITERAL:
        case LM_MATRIX_LITERAL:
            *status |= otree_parse_literal(ast, otree);
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
            (strcmp(ast->children[i]->contents, ";") == 0) ||
            (strcmp(ast->children[i]->tag, "string") == 0) ||
            (strcmp(ast->children[i]->tag, "regex") == 0))
            continue;
        prev = SLL_insert_after(otree->children,
                                ast_2_otree(ast->children[i], status),
                                prev);
    }
    return otree;
}
