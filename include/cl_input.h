/* Command line input utilities
 *
 * Duncan and Anna SoftSys Project 1
 */

#ifndef MINI_LISP_CL_INPUT_H
#define MINI_LISP_CL_INPUT_H

#include "dll.h"
#include "sll.h"
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

DLL *history_dll;

/* One more than the number of characters read at a time from the command line.
 * Cannot be <3. */
#define IN_BUFF_LEN (size_t)5

#define IN_BUFF_MIN_2 (IN_BUFF_LEN - 2)
#define IN_BUFF_MIN_1 (IN_BUFF_LEN - 1)


/** Reads lines from the specified file stream into the history_dll list.
 *
 * A new string is allocated on the heap and pointed to by the newly appended
 * node the history_dll. It is the caller's responsibility to free this memory.
 *
 * @param Data stream to read lines from.
 */
void read_line_into_history(FILE *strm);


#ifdef __cplusplus
}
#endif

#endif //MINI_LISP_CL_INPUT_H
