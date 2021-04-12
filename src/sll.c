/* Singly linked list
 *
 * Duncan and Anna SoftSys Project 1
 */

#include "../include/sll.h"

#ifdef __cplusplus
extern "C" {
#endif


SLL *SLL_create() {
    SLL *sll = malloc(sizeof(SLL));
    if (!sll)
        return sll;

    sll->head = NULL;
    sll->len = 0;
    return sll;
}


SLL_Node *SLL_insert(SLL *const sll, void *const val) {
    SLL_Node *new_node = malloc(sizeof(SLL_Node));
    if (!new_node)
        return new_node;
    new_node->val = val;

    new_node->next = sll->head;
    sll->head = new_node;
    sll->len++;
    return new_node;
}


SLL_Node *
SLL_insert_after(SLL *const sll, void *const val, SLL_Node *const node) {
    SLL_Node *new_node = malloc(sizeof(SLL_Node));
    if (!new_node)
        return new_node;
    new_node->val = val;

    if (node) {
        new_node->next = node->next;
        node->next = new_node;
    } else {
        new_node->next = sll->head;
        sll->head = new_node;
    }
    sll->len++;
    return new_node;
}


SLL_Node *SLL_remove_after(SLL *const sll, SLL_Node *const before_node) {
    SLL_Node *to_delete = before_node->next;
    if (!to_delete)
        return to_delete;
    before_node->next = to_delete->next;
    sll->len--;
    return to_delete;
}

SLL_Node *SLL_remove_first(SLL *const sll) {
    if (!sll->head)
        return sll->head;
    SLL_Node *to_delete = sll->head;
    sll->head = to_delete->next;
    sll->len--;
    return to_delete;
}


void SLL_clean(SLL *const sll) {
    if (!sll->head)  // sll is already empty if true
        return;
    SLL_Node *to_free;
    do {
        to_free = SLL_remove_first(sll);
        SLL_NODE_FREE(to_free);
    } while (sll->head);
    sll->len = 0;
}

#ifdef __cplusplus
}
#endif
