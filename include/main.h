/* Main routine header for mini_lisp
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#ifndef MINI_LISP_MAIN_H
#define MINI_LISP_MAIN_H

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#include "../lib/mpc/mpc.h"

#include "evaluate.h"
#include "dll.h"
#include "grammar.h"
#include "cl_input.h"
#include "otree.h"
#include "builtins.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char *const help_msg;


#ifdef __cplusplus
}
#endif

#endif //MINI_LISP_MAIN_H
