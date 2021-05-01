/* Doubly linked list
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#include "../include/dll.h"

#ifdef __cplusplus
extern "C" {
#endif


DLL *DLL_create() {
    DLL *dll = malloc(sizeof(DLL));
    if (!dll)
        return dll;

    DLL_Node *sentinel = malloc(sizeof(struct DLL_Node));
    if (!sentinel)
        return (DLL *) NULL;

    sentinel->next = sentinel;
    sentinel->val = NULL;
    sentinel->prev = sentinel;
    dll->s = sentinel;
    dll->len = 0;
    return dll;
}


DLL_Node *DLL_append(DLL *const dll, void *const val) {
    DLL_Node *last = dll->s->prev;
    return DLL_insert_after(dll, val, last);
}


DLL_Node *DLL_insert(DLL *const dll, void *const val) {
    DLL_Node *node = dll->s->next;
    return DLL_insert_before(dll, val, node);
}


DLL_Node *
DLL_insert_before(DLL *const dll, void *const val, DLL_Node *const node) {
    DLL_Node *new_node = malloc(sizeof(DLL_Node));
    if (!new_node)
        return new_node;
    new_node->val = val;

    new_node->next = node;
    node->prev->next = new_node;
    new_node->prev = node->prev;
    node->prev = new_node;
    dll->len++;
    return new_node;
}


DLL_Node *
DLL_insert_after(DLL *const dll, void *const val, DLL_Node *const node) {
    DLL_Node *new_node = malloc(sizeof(DLL_Node));
    if (!new_node)
        return new_node;
    new_node->val = val;

    new_node->next = node->next;
    node->next->prev = new_node;
    node->next = new_node;
    new_node->prev = node;
    dll->len++;
    return new_node;
}


void DLL_remove(DLL *const dll, const DLL_Node *const node) {
    // Do nothing if the provided node is the DLL
    if (node == dll->s)
        return;

    node->next->prev = node->prev;
    node->prev->next = node->next;
    dll->len--;
}


void DLL_clean(DLL *const dll) {
    DLL_Node *to_free = dll->s;
    DLL_Node *tmp = to_free->next;

    // Sentinel has a NULL val ptr, so continue until that is reached
    while (tmp != dll->s) {
        to_free = tmp;
        tmp = to_free->next;

        DLL_remove(dll, to_free);
        DLL_NODE_FREE(to_free);
    }
    dll->len = 0;
}


SLL *DLL_to_SLL(DLL *dll) {
    SLL *sll = SLL_create();
    if (sll == NULL) return sll;

    DLL_Node *dll_node = dll->s->next;
    SLL_Node *sll_node = sll->head;
    while (dll_node != dll->s) {
        sll_node = SLL_insert_after(sll, dll_node->val, sll_node);
        dll_node = dll_node->next;
    }
    return sll;
}


#ifdef __cplusplus
}
#endif
