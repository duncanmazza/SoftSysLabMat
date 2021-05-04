/* Evaluation code
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_EVALUATE_H
#define SOFTSYSSOFTSYSLABMAT_EVALUATE_H

#include "ht.h"
#include "otree.h"
#include "binop_funcs.h"


extern HashTable *workspace;
#define WORKSPACE_N_SLOTS 10001
extern HashTable *var_name_to_str_hash;
#define VAR_NAME_TO_STR_HASH_N_SLOTS 10001


int eval_func_call_expr(OTree *otree);

int eval_assmt_stmt(OTree *otree);

int evaluate(OTree* otree);

void print_workspace();

#endif //SOFTSYSSOFTSYSLABMAT_EVALUATE_H
