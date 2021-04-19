//
// Created by duncan on 4/15/21.
//

#include "../include/grammar.h"


SLL *mpc_rules_match(const char *const to_match) {
    const char *rule_matcher = "^\\w+[^\\s]";\
    const char* delimiter = " ;";
    size_t delimiter_len  = strlen(delimiter);

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


int *mpc_setup(mpc_parser_t **parser) {
    const char *grammar =
            "int     : /-?[0-9]+/ ;"
            "float   : /-?([0-9]*[.])[0-9]+/ ;"
            "mth_op  : '+' | '-' | '*' | '/' | '%' ;"
            "bit_op  : '&' | '^' | '|' ;"
            "log_op  : \"&&\" | \"||\" ;"
            "expr    : (<float>|<int>) <mth_op> (<float>|<int>) "
            "        | <int> <bit_op> <int> | <int> <log_op> <int> ;"
            "name    : /[a-zA-Z_][a-zA-Z0-9_]*/ ;"
            "a_stmt  : <name>{1} <name> '=' <expr>';' | <name> '=' <expr>';' ;"
            "stmt    : <a_stmt> ;"
            "lab_mat : /^/ (<stmt>)* /$/ ;";

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
//    mpc_parser_t *p10 = mpc_new(rule_names_arr[10]);
    mpca_lang(MPCA_LANG_DEFAULT, grammar, p00, p01, p02, p03, p04, p05,
              p06, p07, p08, p09);
    *parser = p09;
}
