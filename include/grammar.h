/* Grammar definition
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_GRAMMAR_H
#define SOFTSYSSOFTSYSLABMAT_GRAMMAR_H

#include "../lib/mpc/mpc.h"
#include <regex.h>
#include <sll.h>

#ifdef __cplusplus
extern "C" {
#endif


int mpc_setup(mpc_parser_t **parser);

SLL *mpc_rules_match(const char *to_match);

#ifdef __cplusplus
}
#endif


#endif //SOFTSYSSOFTSYSLABMAT_GRAMMAR_H
