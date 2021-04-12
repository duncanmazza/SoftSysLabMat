/* Doubly linked list
 *
 * Duncan and Anna SoftSys Project 1
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

#ifdef __cplusplus
}
#endif
