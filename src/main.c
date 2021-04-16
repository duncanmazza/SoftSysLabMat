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
    mpc_parser_t *all_parsers[6];
    mpc_parser_t *lab_mat = mpc_setup(all_parsers);

    // Loop for testing command line input
    while (1) {
        printf(">>> ");
        read_line_into_history(stdin);

        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (mpc_parse("input", (char *) history_dll->s->prev->val,
                      lab_mat, &r)) {
            /* print the AST */
            mpc_ast_print(r.output);
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
