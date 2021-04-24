/* Doubly linked list
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_FORMAT_MSG_H
#define SOFTSYSSOFTSYSLABMAT_FORMAT_MSG_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    CTYPE_CHAR,
    CTYPE_INT,
    CTYPE_LONG,
    CTYPE_FLOAT,
    CTYPE_DOUBLE,
    CTYPE_STR,
} CType;

extern const char *const ctype_str_formatting[];


#define QUICK_MSG(msg) format_msg("%s", CTYPE_STR, 1, (msg))
#define QUICK_MSG_ENDL(msg) format_msg("%s\n", CTYPE_STR, 1, (msg))

char *format_msg(const char *templ, CType type, size_t nargs, ...);


int check_str_formatting(const char *templ, size_t num_occurrences,
                         CType type);

#endif //SOFTSYSSOFTSYSLABMAT_FORMAT_MSG_H
