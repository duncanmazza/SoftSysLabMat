/* Hash table
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "ht.h"


size_t hash_str_djb2(HT_KEY_TYPE str) {
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


int HT_get(const HashTable *ht, const unsigned char *key, void **value) {
    size_t str_hash = hash_str_djb2(key);
    DLL* slot = ht->slots[HT_MOD_HASH(str_hash, ht->n_slots)];
    DLL_Node *slot_node = HT_slot_contains(slot, str_hash);
    if (!slot_node) return 1;
    *value = (*(HashTableKVP *)slot_node->val).value;
    return 0;
}


int HT_insert(HashTable *ht, const unsigned char *key, void *value) {
    HashTableKVP *kvp = malloc(sizeof(HashTableKVP));
    if (!kvp) return 1;

    size_t str_hash = hash_str_djb2(key);
    size_t key_hash = HT_MOD_HASH(str_hash, ht->n_slots);
    DLL* slot = ht->slots[key_hash];

    DLL_Node *slot_node = HT_slot_contains(slot, str_hash);
    if (slot_node) {
        DLL_remove(slot, slot_node);
        DLL_NODE_FREE(slot_node);
    }

    kvp->value = value;
    kvp->key = str_hash;
    if (!DLL_append(slot, kvp)) return 1;
    return 0;
}


int HT_remove(HashTable *ht, const unsigned char *key) {
    size_t str_hash = hash_str_djb2(key);
    DLL* slot = ht->slots[HT_MOD_HASH(str_hash, ht->n_slots)];

    DLL_Node *slot_node = HT_slot_contains(slot, str_hash);
    if (slot_node) {
        DLL_remove(slot, slot_node);
        DLL_NODE_FREE(slot_node);
        return 0;
    }
    return 1;
}


DLL_Node * HT_slot_contains(const DLL *slot, size_t str_hash) {
    DLL_Node *node = slot->s->next;
    while (node != slot->s) {
        if (str_hash == (*(HashTableKVP *)node->val).key)
            return node;
        node = node->next;
    }
    return NULL;
}


void HT_clean(HashTable *const ht) {
    for (int i = 0; i < ht->n_slots; i++)
        DLL_clean(ht->slots[i]);
}
