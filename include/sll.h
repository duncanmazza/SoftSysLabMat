/* Doubly linked list
 *
 * Duncan and Anna SoftSys Project 1
 */

#ifndef MINI_LISP_SLL_H
#define MINI_LISP_SLL_H

#include <stdio.h>
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SLL_Node {
    void *val;
    struct SLL_Node *next;
} SLL_Node;


typedef struct {
    SLL_Node *head;
    size_t len;
} SLL;


/* Free the sll node and its val field */
#define SLL_NODE_FREE(sll_node) ({free((sll_node)->val); free(sll_node);})


/** Creates an empty SLL
 *
 * @return Pointer to a SLL struct that was allocated on the heap. If malloc
 *         returns null, then null is returned.
 */
SLL *SLL_create();

/** \brief Inserts a value to the beginning of the SLL
 *
 * If malloc fails to allocate memory, then the value is not inserted.
 *
 * @param sll SLL to insert to
 * @param val Pointer to value to assign to the `val` field of the node created
 *            for insertion
 * @return Pointer to node that was created and inserted in the DLL. If malloc
 *         failed, then NULL is returned.
 */
SLL_Node *SLL_insert(SLL *sll, void *val);


/** \brief Cleans list's memory
 *
 * While sll->head is not null, calls `SLL_remove_first` on the list, then for
 * each node returned by `SLL_remove_first`, frees the memory pointed to by
 * their val fields, and then frees the nodes themselves from memory.
 *
 * @param sll SLL to clean; the resulting SLL will be an emtpy SLL as if just
 *            returned from `SLL_create()`
 */
void SLL_clean(SLL *sll);


/** \brief Insert a value after a given node
 *
 * It is the programmer's responsibility to ensure that the provided SLL does in
 * fact contain the `node` argument.
 *
 * If malloc fails to allocate memory, then the value is not inserted.
 *
 * @param sll SLL that contains the `node` argument
 * @param val Pointer to value to assign to the `val` field of the node created
 *            for insertion. If the null pointer, then behavior is equivalent to
 *            `SLL_insert`.
 * @param node Pointer to the node to insert `val` after
 * @return Pointer to the node that was created and inserted in the SLL. If
 *         malloc failed, then the null pointer is returned.
 */
SLL_Node *
SLL_insert_after(SLL *sll, void *val, SLL_Node *node);


/** \brief Remove the node following the specified node from the SLL
 *
 * It is the programmer's responsibility to ensure that the provided SLL does in
 * fact contain the provided previous node. If the provided node is the last
 * node in the SLL, then nothing about the SLL is changed.
 *
 * @param sll SLL containing the `before_node` argument
 * @param before_node Node whose subsequent node is removed from the SLL
 * @return Node removed from the SLL. In the case that `before_node` is the last
 *         node in the SLL, then the null pointer is returned.
 */
SLL_Node *SLL_remove_after(SLL *sll, SLL_Node *before_node);


/** \brief Remove the first node from the SLL
 *
 * If the sll is empty, then nothing about the SLL is changed.
 *
 * @param sll SLL whose first node is removed.
 * @return Node removed from the SLL. In the case that the SLL is empty, then
 *         the null pointer is returned.
 */
SLL_Node *SLL_remove_first(SLL *sll);

#ifdef __cplusplus
}
#endif

#endif //MINI_LISP_SLL_H
