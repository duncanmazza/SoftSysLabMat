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

const char *const help_msg = \
    "Enter mathematical expressions similar to how you would use MatLab. "
    "Example:\n"
    "\t>>> three = 1 + 2;\n"
    "\t>>> mat = [1, 2; 3, 4];\n"
    "\t>>> mat_added = three + mat;\n"
    "\t>>> mat_mult = [4, 5; 6, 7] * mat_added;\n"
    "\n"
    "To see the variables that are in the workspace, type \"ws\".\n"
    "\t>>> ws\n"
    "\t\n"
    "\tWorkspace:\n"
    "\t----------\n"
    "\t> three (long): 3\n"
    "\t> mat_mult (matrix): \n"
    "\t[8 10\n"
    "\t 12 14]\n"
    "\t> mat_added (matrix): \n"
    "\t[4 5\n"
    "\t 6 7]\n"
    "\t> mat (matrix): \n"
    "\t[1 2\n"
    "\t 3 4]";


int main(int argc, char **argv) {
    mpc_parser_t *parser;
    mpc_setup(&parser);  // TODO: clean memory on exit
    workspace = HT_create(WORKSPACE_N_SLOTS);
    var_name_to_str_hash = HT_create(VAR_NAME_TO_STR_HASH_N_SLOTS);
    if (bind_builtins()) {
        fprintf(stderr, "Failed binding built-in functions");
        exit(-1);
    }

    printf("(enter \"ws\" to print the workspace, \"quit\" to exit, or "
           "\"help\" to display the help message)\n\n");

    // Loop for testing command line input
    char *most_recently_entered;
    while (1) {
        printf(">>> ");
        read_line_into_history(stdin);
        most_recently_entered = (char *) history_dll->s->prev->val;

        if (strcmp(most_recently_entered, "ws\n") == 0 ||
            strcmp(most_recently_entered, "ws;\n") == 0) {
            print_workspace(workspace);
            continue;
        } else if (strcmp(most_recently_entered, "quit\n") == 0 ||
                   strcmp(most_recently_entered, "quit;\n") == 0) {
            break;
        } else if (strcmp(most_recently_entered, "help\n") == 0 ||
                   strcmp(most_recently_entered, "help;\n") == 0) {
            printf("%s\n\n", help_msg);
            continue;
        }

        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (mpc_parse("input", most_recently_entered, parser, &r)) {
            int status = 0;
            OTree *otree = ast_2_otree(r.output, &status);
            if (status != 0) {
                fprintf(stderr,
                        "Cannot evaluate due to static parsing error\n");
                continue;
            }
            evaluate(otree);
            mpc_ast_delete(r.output);
        } else {
            /* Otherwise Print the Error */
            fprintf(stderr, "Syntax error: ");
            mpc_err_print_to(r.error, stderr);
            mpc_err_delete(r.error);
        }
    }
    return 0;
}

#pragma clang diagnostic pop

#ifdef __cplusplus
}
#endif
