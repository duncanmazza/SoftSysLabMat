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


extern HashTable *vars_mapping;
#define VARS_MAPPING_N_SLOTS 2001


int eval_func_call_expr(OTree *otree);

int eval_assmt_stmt(OTree *otree);

int evaluate(OTree* otree);

#endif //SOFTSYSSOFTSYSLABMAT_EVALUATE_H
