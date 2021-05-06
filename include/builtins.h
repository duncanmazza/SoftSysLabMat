/* Built-in functions
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_BUILTINS_H
#define SOFTSYSSOFTSYSLABMAT_BUILTINS_H

#include "matrix.h"
#include "ht.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const char *const builtins_names[];

extern void *(*builtins_func_ptrs[])(size_t, OTree *[]);

extern HashTable *builtins;
#define BUILTINS_SLOTS 2001


void *builtin_transpose(size_t nargs, OTree **args);

int bind_builtins();

#ifdef __cplusplus
}
#endif


#endif //SOFTSYSSOFTSYSLABMAT_BUILTINS_H
