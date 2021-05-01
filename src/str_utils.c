/* Doubly linked list
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#include "str_utils.h"

/* Important note: the strings in this array must correspond exactly to the
* CType enum */
const char *const ctype_str_formatting[] = {
        "%c",
        "%i",
        "%li",
        "%f",
        "%lf",
        "%s",
};

char *sll_strs_to_str(const SLL *const sll, const char *const join_str,
                      const char *const term_str) {
    size_t join_str_len = strlen(join_str);
    size_t term_str_len = strlen(term_str);
    size_t strlen_record[sll->len];
    size_t total_strlen = 0;
    SLL_Node *node = sll->head;
    size_t counter = 0;
    while (node != NULL) {
        strlen_record[counter] = strlen((char *) node->val);
        total_strlen += strlen_record[counter] + join_str_len;
        node = node->next;
        counter++;
    }

    // Size will be total_strlen with another character for '\0' with the last
    // join_str_len counted for in the above while loop replaced by term_str_len
    char *str_repr = malloc(total_strlen + 1 + term_str_len - join_str_len);
    str_repr[total_strlen] = '\0';
    char *const str_repr_copy = str_repr;
    node = sll->head;
    counter = 0;
    while (node != NULL) {
        strcpy(str_repr, (char *) node->val);
        str_repr += strlen_record[counter++];
        node = node->next;
        if (node != NULL) {
            strcpy(str_repr, join_str);
            str_repr += join_str_len;
        } else {
            strcpy(str_repr, term_str);
        }
    }
    return str_repr_copy;
}


char *format_msg(const char *templ, CType type,
                 const int skip_check, size_t nargs, ...) {
    if (!skip_check) {
        if (!check_str_formatting(templ, nargs, type)) {
            fprintf(stderr, "Message template did not contain the appropriate "
                            "number of %s substrings to support string "
                            "formatting", ctype_str_formatting[type]);
            exit(-1);
        }
    }

    va_list ap;
    va_start(ap, nargs);

    // Determine an appropriate size for the buffer
    size_t msg_buffer_len = strlen(templ + 1);
    switch (type) {
        case CTYPE_CHAR:
            msg_buffer_len += nargs;
            break;
        case CTYPE_STR:
            for (int i = 0; i < nargs; i++) {
                msg_buffer_len += strlen(va_arg(ap, char *));
            }
            // Reset ap
            va_start(ap, nargs);
            break;
        default:
            // Arbitrarily large increment coefficient of 20
            msg_buffer_len += 20 * nargs;
            break;
    }
    char *msg_buffer = malloc(msg_buffer_len);
    memset(msg_buffer, '\0', msg_buffer_len);
    vsprintf(msg_buffer, templ, ap);
    return msg_buffer;
}


int check_str_formatting(const char *const templ, const size_t num_occurrences,
                         CType type) {
    // Check for instances of any of the other string formatting strings
    int any = 0;
    for (int i = 0; i < sizeof(ctype_str_formatting) / sizeof(char *); i++) {
        if (i == type && num_occurrences != 0)
            continue;
        if (strstr(templ, ctype_str_formatting[i])) {
            any |= 1;
        }
    }

    if (num_occurrences == 0)
        return any == 0;
    else {
        if (any != 0)
            return 0;
    }

    size_t count = 0;
    char *tmp;
    tmp = strstr(templ, ctype_str_formatting[type]);
    while (tmp) {
        count++;
        tmp = strstr(tmp + 1, ctype_str_formatting[type]);
    }
    return num_occurrences == count;
}

