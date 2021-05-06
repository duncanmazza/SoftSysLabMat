/* Built-in functions
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include <otree.h>
#include "builtins.h"


const char *const builtins_names[] = {
        "transpose",
};

void *(*builtins_func_ptrs[])(size_t, OTree *[]) = {
        builtin_transpose,
};


HashTable *builtins;


int bind_builtins() {
    builtins = HT_create(BUILTINS_SLOTS);
    for (int i = 0; i < sizeof(builtins_names) / sizeof(char *); i++) {
        if (HT_insert(builtins, (HT_KEY_TYPE) builtins_names[i],
                      builtins_func_ptrs[i])) {
            return 1;
        };
    }
    return 0;
}


void *builtin_transpose(size_t nargs, OTree **args) {
    if (nargs != 1) {
        fprintf(stderr,
                "builtin_transpose provided with more than one argument");
        exit(-1);
    }
    OTree *mat_otree = (OTree *) args[0];
    *(matrix *) mat_otree->val = *matrix_transpose((matrix *) mat_otree->val);
    return mat_otree;
}
