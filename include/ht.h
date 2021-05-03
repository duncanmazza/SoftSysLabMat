/* Hash table
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_HT_H
#define SOFTSYSSOFTSYSLABMAT_HT_H

#include "dll.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    size_t n_slots;
    DLL **slots;
} HashTable;

typedef struct {
    size_t key;
    void *value;
} HashTableKVP;  // Key value pair


HashTable *HT_create(size_t n_slots);

/** djb2 string hashing function
 *
 * Credit to Dan Bernstein for first proposing this algorithm. Slightly adapted
 * from the version at http://www.cse.yorku.ca/~oz/hash.html.
 *
 * @param str String to hash
 * @return Hash
 */
unsigned long hash_str_djb2(const unsigned char *str);

/** Insert a value into the hash table
 *
 * If malloc fails to allocate memory, then the value is not inserted.
 *
 * If the key already exists in the hash table, then the old value is removed
 * (including being freed from memory) regardless of whether the value ended up
 * being inserted.
 *
 *
 * @param ht Hash table to insert into
 * @param key Key corresponding to the value
 * @param value Value to insert
 * @return Zero successful, 1 otherwise
 */
int HT_insert(HashTable *ht, const unsigned char *key, void *value);

/** Checks whether a slot contains a node with the specified key.
 *
 * @param slot Hash table slot
 * @param str_hash Key to search for
 * @return Pointer to the node if it is contained, NULL otherwise.
 */
DLL_Node * HT_slot_contains(const DLL* slot, size_t str_hash);

/** Gets the value associated with the provided key.
 *
 * @param ht Hash table to look up
 * @param key Key to query
 * @param value Modified to point to the value at the key if the key is present
 *              in the hash table
 * @return 0 if the key is present and 1 otherwise
 */
int HT_get(const HashTable * ht, const unsigned char * key, void **value);


/** Removes the specified key-value pair from the hash table (including freeing
 * it from memory).
 *
 * @param ht Hash table to remove from
 * @param key Key of the key-value pair to remove and free
 * @return 0 if key-value pair was present and removed and 1 otherwise.
 */
int HT_remove(HashTable *ht, const unsigned char *key);


/** Runs DLL_clean on all of the slots
 *
 * @param ht Hash table to clean
 */
void HT_clean(HashTable *ht);


#define HT_MOD_HASH(key, n_slots) ((key) % (n_slots))

#define HT_KEY_TYPE const unsigned char *const

#define HT_FREE(ht) ({                                                         \
    for (int i = 0; i < (ht)->n_slots; i++) {                                  \
        DLL_clean((ht)->slots[i]);                                             \
        DLL_FREE((ht)->slots[i]);                                              \
    }                                                                          \
    free((ht)->slots);                                                         \
    free(ht);                                                                  \
})


#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_HT_H
