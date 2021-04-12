/* Command line input utilities
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#include "../include/cl_input.h"

#ifdef __cplusplus
extern "C" {
#endif


void read_line_into_history(FILE *strm) {
    if (!history_dll)
        history_dll = DLL_create();

    SLL *sll_of_inputs = SLL_create();
    SLL_Node *node = NULL;
    char *input_on_heap;
    char in_buff[IN_BUFF_LEN];

    do {
        memset(in_buff, '\0', IN_BUFF_LEN);
        fgets(in_buff, IN_BUFF_LEN, strm);
        input_on_heap = malloc(sizeof(in_buff));
        strcpy(input_on_heap, in_buff);
        node = SLL_insert_after(sll_of_inputs, input_on_heap, node);
    } while (!feof(strm) &&
             in_buff[IN_BUFF_MIN_2] != '\n' &&
             in_buff[IN_BUFF_MIN_2] != '\0');

    fflush(strm);
    node = sll_of_inputs->head;
    size_t num_chars = IN_BUFF_MIN_1 * sll_of_inputs->len;
    size_t total_buff_sz = sizeof(char) * num_chars + 1;
    char *total_buff = malloc(total_buff_sz);
    total_buff[num_chars - 1] = '\0';

    for (size_t i = 0; i < sll_of_inputs->len; i++) {
        strcpy(total_buff + IN_BUFF_MIN_1 * i, (char *) node->val);
        node = node->next;
    }

    // Record in history
    DLL_append(history_dll, total_buff);

    // Memory cleanup
    SLL_clean(sll_of_inputs);
    free(sll_of_inputs);
}


#ifdef __cplusplus
}
#endif
