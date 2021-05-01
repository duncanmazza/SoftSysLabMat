/* Hash table
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "ht.h"


inline size_t hash_str_djb2(HT_KEY_TYPE str) {
    const unsigned char* str_ptr_cpy = (const unsigned char*)str;
    size_t hash = 5381;
    int c;
    while ((c = *str_ptr_cpy++))
        hash = ((hash << 5) + hash) + c;  /* hash * 33 + c */
    return hash;
}


HashTable *HT_create(size_t n_slots) {
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht)
        return ht;

    ht->n_slots = n_slots;
    ht->slots = malloc(sizeof(DLL) * n_slots);
    for (int slot_idx = 0; slot_idx < n_slots; slot_idx++) {
        ht->slots[slot_idx] = DLL_create();
        if (!ht->slots[slot_idx]) {
            for (int i = 0; i < slot_idx; i++) {
                free(ht->slots[i]);
            }
            free(ht);
            return NULL;
        }
    }
    return ht;
}


int HT_get(const HashTable *const ht, HT_KEY_TYPE key, size_t *const value) {
    DLL* slot = HT_ACQUIRE_SLOT(ht, key);
    DLL_Node *slot_node = HT_slot_contains(slot, key);
    if (!slot_node) return 1;
    *value = *(size_t *)slot_node->val;
}


int HT_insert(HashTable *ht, const unsigned char *key, size_t value) {
    size_t *heap_value = malloc(sizeof(size_t));
    if (!heap_value) return 1;

    DLL* slot = HT_ACQUIRE_SLOT(ht, key);

    DLL_Node *slot_node = HT_slot_contains(slot, key);
    if (slot_node) {
        DLL_remove(slot, slot_node);
        DLL_NODE_FREE(slot_node);
    }
    
    *heap_value = value;
    if (!DLL_append(slot, heap_value)) return 1;
    return 0;
}


DLL_Node * HT_slot_contains(const DLL *slot, const unsigned char *key) {
    DLL_Node *node = slot->s->next;
    while (node != slot->s) {
        if (HT_KEY_EQUAL(key, (HT_KEY_TYPE)node->val))
            return node;
        node = node->next;
    }
    return NULL;
}


void HT_clean(HashTable *const ht) {
    for (int i = 0; i < ht->n_slots; i++) {
        DLL_FREE(ht->slots[i]);
    }
    free(ht->slots);
    free(ht);
}

