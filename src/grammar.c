/* Grammar definition
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */


#include "../include/grammar.h"


SLL *mpc_rules_match(const char *const to_match) {
    const char *rule_matcher = "^\\w+[^\\s]";\
    const char *delimiter = " ;";
    size_t delimiter_len = strlen(delimiter);

    regex_t rx;
    int regex_comp_ret = regcomp(&rx, rule_matcher, REG_EXTENDED);
    if (regex_comp_ret != 0) {
        printf("Regex compiled with error");
        exit(-1);
    }

    SLL *rule_definitions = SLL_create();
    SLL_Node *prev_rule_def = NULL;
    size_t grammar_len = strlen(to_match);
    char *to_match_copy = malloc(grammar_len + 1);
    char *to_match_copy_copy = to_match_copy;
    strcpy(to_match_copy, to_match);
    char *next_found = strstr(to_match_copy, delimiter);
    while (next_found != NULL) {
        size_t token_len = (next_found - to_match_copy);
        char *token = malloc(token_len);
        strncpy(token, to_match_copy, token_len);
        prev_rule_def = SLL_insert_after(rule_definitions, token,
                                         prev_rule_def);
        to_match_copy = next_found + delimiter_len;
        next_found = strstr(to_match_copy, delimiter);
    }

    SLL *rule_names = SLL_create();
    SLL_Node *rule_def_node = rule_definitions->head;
    SLL_Node *prev_rule_name = NULL;
    regmatch_t rx_match;
    while (rule_def_node) {
        if (regexec(&rx, (char *) rule_def_node->val, 1, &rx_match, 0)) {
            fprintf(stderr,
                    "No matches found when looking for a mpc rule name");
            exit(-1);
        }
        size_t rule_name_len = rx_match.rm_eo - rx_match.rm_so - 1;
        char *rule_name = malloc(rule_name_len + 1);
        rule_name[rule_name_len] = '\0';
        strncpy(rule_name, (char *) rule_def_node->val + rx_match.rm_so,
                rule_name_len);
        prev_rule_name = SLL_insert_after(rule_names, rule_name,
                                          prev_rule_name);

        rule_def_node = rule_def_node->next;
    }

    regfree(&rx);
    free(to_match_copy_copy);
    SLL_clean(rule_definitions);
    return rule_names;
}


int mpc_setup(mpc_parser_t **parser) {
    const char *grammar =
            // -- Atomic rules --
            "int     : /-?[0-9]+/ ;"  // Integer number
            "float   : /-?[0-9]+[.][0-9]+/ ;"  // Floating point number
            "math_op : '+' | '-' | '*' | '/' | '%' ;"  // Arithmetic operators
            "bit_op  : '&' | '^' | '|' ;"  // Bit operators
            "log_op  : \"&&\" | \"||\" ;"  // Logical operators
            "assmt   : '=' ;"  // Assignment operator

            "allchar : /[^\"]*/ ;"  // Do not allow double quotes
            "name    : /[a-zA-Z_][a-zA-Z0-9_]*/ ;"  // Any valid token name
            "mat_dlm : (',' | ' ') | ';' ;"  // Matrix delimiter
            "al_dlm  : ','/\s*/ ;"  // Argument list delimiter

            // -- Compound rules --
            "num     : <float> | <int> ;"  // [order matters] Any number
            "str_lit : '\"'<allchar>'\"' ;"  // String literal
            "mat_lit : '['((<num><mat_dlm>)+ <num>?)']' ;"  // Matrix literal
            "smpexpr : <num> <math_op> <num> "  // Simple expression
            "        | <int> (<log_op> | <bit_op>) <int> "  // [order matters]
            "        | <str_lit> "
            "        | <num> "
            "        | <mat_lit> "
            "        | <name> ;"
            "arglist : ((<smpexpr><al_dlm>)+<smpexpr> | <smpexpr>) ;"
            "fexpr   : <name>'('/\s*/<arglist>?/\s*/')' ;"  // Expression: function call
            "anyexpr : ('('(<fexpr> | <smpexpr>)')') | (<fexpr> | <smpexpr>) ;"
            "a_stmt  : (<name> <name> <assmt> <anyexpr> "  // Assignment statement
            "        | <name> <assmt> <anyexpr>"
            "        | <fexpr>)';' ;"
            "stmt    : <a_stmt> ;"
            "lab_mat : /^/ ((<stmt>)/\s*/)+ /$/ ;";

    SLL *matched_rule_names = mpc_rules_match(grammar);
    char *rule_names_arr[matched_rule_names->len];
    SLL_Node *rule_node = matched_rule_names->head;
    for (int i = 0; i < matched_rule_names->len; i++) {
        rule_names_arr[i] = (char *) rule_node->val;
        rule_node = rule_node->next;
    }

    // mpc only allows this method of creating a language parser through a
    // variadic function, so manually create every parser needed in the scope.
    // The number of rules in the grammar needs to correspond to the number of
    // parsers.
    mpc_parser_t *p00 = mpc_new(rule_names_arr[0]);
    mpc_parser_t *p01 = mpc_new(rule_names_arr[1]);
    mpc_parser_t *p02 = mpc_new(rule_names_arr[2]);
    mpc_parser_t *p03 = mpc_new(rule_names_arr[3]);
    mpc_parser_t *p04 = mpc_new(rule_names_arr[4]);
    mpc_parser_t *p05 = mpc_new(rule_names_arr[5]);
    mpc_parser_t *p06 = mpc_new(rule_names_arr[6]);
    mpc_parser_t *p07 = mpc_new(rule_names_arr[7]);
    mpc_parser_t *p08 = mpc_new(rule_names_arr[8]);
    mpc_parser_t *p09 = mpc_new(rule_names_arr[9]);
    mpc_parser_t *p10 = mpc_new(rule_names_arr[10]);
    mpc_parser_t *p11 = mpc_new(rule_names_arr[11]);
    mpc_parser_t *p12 = mpc_new(rule_names_arr[12]);
    mpc_parser_t *p13 = mpc_new(rule_names_arr[13]);
    mpc_parser_t *p14 = mpc_new(rule_names_arr[14]);
    mpc_parser_t *p15 = mpc_new(rule_names_arr[15]);
    mpc_parser_t *p16 = mpc_new(rule_names_arr[16]);
    mpc_parser_t *p17 = mpc_new(rule_names_arr[17]);
    mpc_parser_t *p18 = mpc_new(rule_names_arr[18]);
    mpc_parser_t *p19 = mpc_new(rule_names_arr[19]);
    mpca_lang(MPCA_LANG_DEFAULT, grammar, p00, p01, p02, p03, p04, p05,
              p06, p07, p08, p09, p10, p11, p12, p13, p14, p15, p16, p17, p18,
              p19);
    *parser = p19;
    return 20;
}
