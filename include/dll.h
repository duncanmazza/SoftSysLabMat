/* Doubly linked list
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#ifndef MINI_LISP_DLL_H
#define MINI_LISP_DLL_H

#include "sll.h"
#include <stdio.h>
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DLL_Node {
    struct DLL_Node *prev;
    void *val;
    struct DLL_Node *next;
} DLL_Node;


typedef struct {
    DLL_Node *s;  // Sentinel
    size_t len;
} DLL;


/* Free the dll and the sentinel node (but not the next and prev fields of the
 * sentinel because it is assumed that the dll is empty when this is called, in
 * which case they are pointing to the sentinel itself) */
#define DLL_FREE(dll) ({free((dll)->s); free(dll);})

/* Free the dll node and its val field */
#define DLL_NODE_FREE(dll_node) ({free((dll_node)->val); free(dll_node);})


/** Create an empty DLL
 *
 * @return Pointer to a DLL struct that was allocated on the heap. If malloc
 *         fails for allocating either the DLL struct or the DLL sentinel node,
 *         the null pointer is returned.
 */
DLL *DLL_create();


/** \brief Append a value to the end of a given DLL
 *
 * This runs in constant time because the DLL is implemented with a sentinel
 * node, so there is an O(1) access time to the tail node. If malloc fails to
 * allocate memory, then the value is not inserted.
 *
 * @param dll DLL to append to
 * @param val Pointer to value to assign to the `val` field of the node created
 *            for appending
 * @return Pointer to node that was created and appended to the DLL. If malloc
 *         failed, then NULL is returned.
 */
DLL_Node *DLL_append(DLL *dll, void *val);


/** \brief Insert a value before a given node
 *
 * It is the programmer's responsibility to ensure that the provided DLL does in
 * fact contain the provided previous node. If malloc fails to allocate memory,
 * then the value is not inserted.
 *
 * @param dll DLL that contains the `prev_node` param; its length field is
 *            incremented by 1 when the value is inserted
 * @param val Pointer to value to assign to the `val` field of the node created
 *            for insertion
 * @param node Pointer to the node to insert the `val` before
 * @return Pointer to node that was created and insert in the DLL. If malloc
 *         failed, then NULL is returned.
 */
DLL_Node *
DLL_insert_before(DLL *dll, void *val, DLL_Node *node);


/** \brief Insert a value to the beginning of a given DLL.
 *
 * If malloc fails to allocate memory, then the value is not inserted.
 *
 * @param dll DLL to insert to
 * @param val Pointer to value to assign to the `val` field of the node created
 *            for insertion
 * @return Pointer to node that was created and inserted in the DLL. If malloc
 *         failed, then NULL is returned.
 */
DLL_Node *DLL_insert(DLL *dll, void *val);


/** \brief Clean list's memory
 *
 * Iterates through all nodes in the dll, calls `DLL_remove` on them,
 * frees the memory pointed to by their val fields, and then frees the nodes
 * themselves from memory.
 *
 * @param dll DLL to clean; the resulting DLL will be an empty DLL as if just
 *            returned from `DLL_create()`
 */
void DLL_clean(DLL *dll);


/** \brief Insert a value before a given node
 *
 * It is the programmer's responsibility to ensure that the provided DLL does in
 * fact contain the `node` argument.
 *
 * If malloc fails to allocate memory, then the value is not inserted.
 *
 * @param dll DLL that contains the `prev_node` argument
 * @param val Pointer to value to assign to the `val` field of the node created
 *            for insertion
 * @param node Pointer to the node to insert `val` before
 * @return Pointer to the node that was created and inserted in the DLL. If
 *         malloc failed, then the null pointer is returned.
 */
DLL_Node *
DLL_insert_after(DLL *dll, void *val, DLL_Node *node);


/** \brief Remove a node from the dll
 *
 * It is the programmer's responsibility to ensure that the provided DLL does in
 * fact contain the `node` argument. If the passed node is the sentinel, then
 * nothing happens.
 *
 * @param dll DLL to remove from; its length is decremented by 1
 * @param node Node to remove from the DLL
 */
void DLL_remove(DLL *dll, const DLL_Node *node);


/** \brief Shallow-copies a dll to a sll (prev pointers are ignored)
 *
 * It is the programmer's responsibility to free the allocated memory.
 *
 * @param dll
 * @return Newly allocated SLL
 */
SLL *DLL_to_SLL(DLL *dll);


#ifdef __cplusplus
}
#endif

#endif //MINI_LISP_DLL_H
