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

    TEST(HT_Tests, HT_Insert_Get) {
        HashTable *ht = HT_create(41);
        HT_insert(ht, (HT_KEY_TYPE) "key1", 1);
        HT_insert(ht, (HT_KEY_TYPE) "key2", 2);
        HT_insert(ht, (HT_KEY_TYPE) "key3", 3);

        size_t got;
        HT_get(ht, (HT_KEY_TYPE) "key1", &got);
        ASSERT_EQ(got, 1);
        HT_get(ht, (HT_KEY_TYPE) "key2", &got);
        ASSERT_EQ(got, 2);
        HT_get(ht, (HT_KEY_TYPE) "key3", &got);
        ASSERT_EQ(got, 3);
    }

} // namespace HT_Gtests

#pragma clang diagnostic pop
