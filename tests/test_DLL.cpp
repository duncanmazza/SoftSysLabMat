/* Doubly linked list testing
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 * Acknowledgement: The code in this file was adapted from the ArticulateLisp
 * project authored by Duncan Mazza and Anna Griffin.
 *
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"


#include "../include/dll.h"
#include "test_all.hpp"

namespace DLL_Gtests {

#define ASSERT_EMPTY_DLL(dll) ({                                               \
    ASSERT_EQ((dll)->len, 0);                                                  \
    ASSERT_EQ((dll)->s->next, (dll)->s);                                       \
    ASSERT_EQ((dll)->s->prev, (dll)->s);                                       \
    ASSERT_EQ((typeof(NULL)) (dll)->s->val, NULL);                             \
})

    NUM_VECS  // Create the num_vecs variable

    TEST(DLL_Tests, DLL_Create) {
        DLL *dll = DLL_create();
        ASSERT_EMPTY_DLL(dll);
        DLL_clean(dll);
        DLL_FREE(dll);
    }

    TEST(DLL_Tests, DLL_Append) {
        DLL *dll;
        for (auto &num_vec : num_vecs) {
            dll = DLL_create();
            POPULATE_LL(dll, num_vec, &DLL_append);

            // Check forward links
            DLL_Node *node = dll->s->next;
            int idx{0};
            while (node != dll->s) {
                // Prevent accidental infinite loop
                ASSERT_LT(idx, num_vec.size());
                ASSERT_EQ(*(int *) (node->val), num_vec.at(idx));
                node = node->next;
                idx++;
            }

            // Check backward links
            node = dll->s->prev;
            idx = (int) num_vec.size() - 1;
            while (node != dll->s) {
                // Prevent accidental infinite loop
                ASSERT_GT(idx, -1);  // Prevent accidental infinite loop
                ASSERT_EQ(*(int *) (node->val), num_vec.at(idx));
                node = node->prev;
                idx--;
            }
            DLL_clean(dll);
            DLL_FREE(dll);
        }
    }

    TEST(DLL_Tests, DLL_Insert) {
        DLL *dll;
        for (auto &numVec : num_vecs) {
            dll = DLL_create();
            POPULATE_LL(dll, numVec, &DLL_insert);

            // Check forward links
            DLL_Node *node = dll->s->prev;
            int idx{0};
            while (node != dll->s) {
                // Prevent accidental infinite loop
                ASSERT_LT(idx, numVec.size());

                ASSERT_EQ(*(int *) (node->val), numVec.at(idx));
                node = node->prev;
                idx++;
            }

            // Check backward links
            node = dll->s->next;
            idx = (int) numVec.size() - 1;
            while (node != dll->s) {
                // Prevent infinite looping in case there is a cycle in the DLL
                ASSERT_GT(idx, -1);  // Prevent accidental infinite loop
                ASSERT_EQ(*(int *) (node->val), numVec.at(idx));
                node = node->next;
                idx--;
            }
            DLL_clean(dll);
            DLL_FREE(dll);
        }
    }

    TEST(DLL_Tests, DLL_Delete) {
        DLL *dll = DLL_create();
        DLL_Node *orig_s = dll->s;

        // Test attempting to remove sentinel (nothing should happen)
        DLL_remove(dll, dll->s);
        ASSERT_EQ(dll->s, orig_s);
        ASSERT_EQ((typeof(NULL)) dll->s->val, NULL);
        ASSERT_EMPTY_DLL(dll);

        // Add one node, then test deleting it
        int *val1 = HEAP_INT;
        *val1 = 1;  // Assign arbitrary value
        DLL_append(dll, val1);
        DLL_Node *to_remove = dll->s->next;
        DLL_remove(dll, to_remove);
        // Check that the dll is as if it was just created
        ASSERT_EQ(dll->s, orig_s);
        ASSERT_EMPTY_DLL(dll);
        // Check that the returned node is not affected
        ASSERT_EQ(*(int *) to_remove->val, *val1);
        ASSERT_EQ(to_remove->next, dll->s);
        ASSERT_EQ(to_remove->prev, dll->s);

        DLL_clean(dll);
        DLL_NODE_FREE(to_remove);
        DLL_FREE(dll);
    }

    TEST(DLL_Tests, DLL_Clean) {
        DLL *dll = DLL_create();
        DLL_Node *orig_s = dll->s;

        // Test cleaning an empty DLL
        DLL_clean(dll);
        ASSERT_EQ(dll->s, orig_s);
        ASSERT_EMPTY_DLL(dll);

        for (auto &numVec : num_vecs) {
            POPULATE_LL(dll, numVec, &DLL_append);
            DLL_clean(dll);
            ASSERT_EQ(dll->s, orig_s);
            ASSERT_EMPTY_DLL(dll);
        }
        DLL_FREE(dll);
    }
} // namespace DLL_Gtests

#pragma clang diagnostic pop
