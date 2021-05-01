/* Hash table testing
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"


#include "../include/ht.h"
#include "test_all.hpp"

namespace HT_Gtests {

// Ideally, a large prime number not close to a power of 2
#define NUM_SLOTS 1001

    TEST(HT_Tests, HT_Insert_Get) {
        HashTable *ht = HT_create(NUM_SLOTS);
        int one = 1;
        int two = 2;
        int three = 3;
        int four = 4;
        HT_insert(ht, (HT_KEY_TYPE) "key1", &one);
        HT_insert(ht, (HT_KEY_TYPE) "key2", &two);
        HT_insert(ht, (HT_KEY_TYPE) "key3", &three);

        void *got;
        HT_get(ht, (HT_KEY_TYPE) "key1", &got);
        ASSERT_EQ(got, &one);
        ASSERT_EQ(*(int *)got, one);
        HT_get(ht, (HT_KEY_TYPE) "key2", &got);
        ASSERT_EQ(got, &two);
        ASSERT_EQ(*(int *)got, two);
        HT_get(ht, (HT_KEY_TYPE) "key3", &got);
        ASSERT_EQ(got, &three);
        ASSERT_EQ(*(int *)got, three);


        // Test overriding an existing key
        HT_insert(ht, (HT_KEY_TYPE) "key3", &four);
        HT_get(ht, (HT_KEY_TYPE) "key3", &got);
        ASSERT_EQ(got, &four);
        ASSERT_EQ(*(int *)got, four);

        HT_clean(ht);
        HT_FREE(ht);
    }

    TEST(HT_Tests, HT_Insert_Get_Remove) {
        HashTable *ht = HT_create(NUM_SLOTS);
        int one = 1;
        int two = 2;
        int three = 3;
        HT_insert(ht, (HT_KEY_TYPE) "key1", &one);
        HT_insert(ht, (HT_KEY_TYPE) "key2", &two);
        HT_insert(ht, (HT_KEY_TYPE) "key3", &three);

        void *got;
        HT_get(ht, (HT_KEY_TYPE) "key1", &got);
        ASSERT_EQ(got, &one);
        ASSERT_EQ(*(int *)got, one);
        HT_get(ht, (HT_KEY_TYPE) "key2", &got);
        ASSERT_EQ(got, &two);
        ASSERT_EQ(*(int *)got, two);
        HT_get(ht, (HT_KEY_TYPE) "key3", &got);
        ASSERT_EQ(got, &three);
        ASSERT_EQ(*(int *)got, three);

        int ret_val;
        ret_val = HT_remove(ht, (HT_KEY_TYPE) "key1");
        ASSERT_EQ(ret_val, 0);
        ret_val = HT_remove(ht, (HT_KEY_TYPE) "key2");
        ASSERT_EQ(ret_val, 0);
        ret_val = HT_remove(ht, (HT_KEY_TYPE) "key3");
        ASSERT_EQ(ret_val, 0);

        // Test removing a key-value pair that is not present
        ret_val = HT_remove(ht, (HT_KEY_TYPE) "key1");
        ASSERT_EQ(ret_val, 1);

        HT_clean(ht);
        HT_FREE(ht);
    }

} // namespace HT_Gtests

#pragma clang diagnostic pop
