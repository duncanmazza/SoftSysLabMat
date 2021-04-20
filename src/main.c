/* Main routine for LabMat
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#include "../include/main.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main(int argc, char **argv) {
    mpc_parser_t *parser;
    int num_parsers = mpc_setup(&parser);

    // Loop for testing command line input
    while (1) {
        printf(">>> ");
        read_line_into_history(stdin);

        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (mpc_parse("input", (char *) history_dll->s->prev->val,
                      parser, &r)) {
            /* print the AST */
            mpc_ast_print(r.output);

            int status;
            ast_2_otree(r.output, &status);
            if (status != 0) {
                fprintf(stderr, "Cannot evaluate due to static parsing error");
                continue;
            }

            mpc_ast_delete(r.output);
        } else {
            /* Otherwise Print the Error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
    }

    return 0;
}

#pragma clang diagnostic pop

#ifdef __cplusplus
}
#endif
