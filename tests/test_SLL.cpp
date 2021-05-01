/* Singly linked list testing
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


#include "../include/sll.h"
#include "test_all.hpp"


namespace SLL_Gtests {
#define ASSERT_EMPTY_SLL(sll) ({                                               \
    ASSERT_EQ((sll)->len, 0);                                                  \
    ASSERT_EQ((typeof(NULL))(sll)->head, NULL);                                \
})

    NUM_VECS  // Create the num_vecs variable

    TEST(SLL_Tests, SLL_Create) {
        SLL *sll = SLL_create();
        ASSERT_EMPTY_SLL(sll);
        free(sll);
    }

    TEST(SLL_Tests, SLL_Delete_after_and_insert_after) {
        // Create SLL with integers in the order: 1, 2, 3
        SLL *sll = SLL_create();
        int *i_heap = HEAP_INT;
        *i_heap = 3;
        SLL_insert(sll, i_heap);
        i_heap = HEAP_INT;
        *i_heap = 1;
        SLL_insert(sll, i_heap);
        i_heap = HEAP_INT;
        *i_heap = 2;

        // Insert node in the middle
        SLL_Node *inserted_after = SLL_insert_after(sll, i_heap, sll->head);

        // Check that the SLL was updated correctly
        ASSERT_EQ(inserted_after->val, i_heap);
        ASSERT_EQ(*(int *) inserted_after->val, 2);
        ASSERT_EQ(3, sll->len);
        SLL_Node *node = sll->head;
        int loop_counter = 1;
        do {
            // Prevent accidental infinite loop
            ASSERT_LT(loop_counter, 4);
            ASSERT_EQ(*(int *) node->val, loop_counter);
            node = node->next;
            loop_counter++;
        } while (node->next);

        // Insert node at the end such that the sll contains 1, 2, 3, 4
        i_heap = HEAP_INT;
        *i_heap = 4;
        inserted_after = SLL_insert_after(sll, i_heap, node);

        // Check that the SLL was updated correctly
        ASSERT_EQ(inserted_after->val, i_heap);
        ASSERT_EQ(*(int *) inserted_after->val, 4);
        ASSERT_EQ(node->next, inserted_after);
        ASSERT_EQ((typeof(NULL)) inserted_after->next, NULL);
        ASSERT_EQ(4, sll->len);


        // At this point, the node var is pointing to the second-to-last node
        // so use this to test SLL_remove_after on the last node
        SLL_Node *removed_after = SLL_remove_after(sll, node->next);
        ASSERT_EQ(NULL, (typeof(NULL)) removed_after);
        ASSERT_EQ(4, sll->len);

        // Test SLL_remove_after on the second-to-last node
        removed_after = SLL_remove_after(sll, node);
        // inserted_after is still pointing to the last node before it was
        // removed, so make sure that this is what was returned
        ASSERT_EQ(inserted_after, removed_after);
        ASSERT_EQ(inserted_after->val, removed_after->val);
        ASSERT_EQ(NULL, (typeof(NULL)) removed_after->next);
        ASSERT_EQ(NULL, (typeof(NULL)) node->next);
        ASSERT_EQ(3, sll->len);
        SLL_NODE_FREE(removed_after);

        // At this point, the sll is back to containing 1, 2, 3

        // Test SLL_remove_after on the first node
        removed_after = SLL_remove_after(sll, sll->head);

        // Check that the sll was updated correctly and is now containing 1, 3
        ASSERT_EQ(1, *(int *) sll->head->val);
        ASSERT_EQ(3, *(int *) sll->head->next->val);
        ASSERT_EQ(2, *(int *) removed_after->val);
        ASSERT_EQ(sll->head->next, removed_after->next);
        ASSERT_EQ(2, sll->len);
        SLL_NODE_FREE(removed_after);

        // Test passing NULL to SLL_insert_after
        i_heap = HEAP_INT;
        *i_heap = 0;
        inserted_after = SLL_insert_after(sll, i_heap, nullptr);

        // Check that the sll was updated correctly and is now containing 0, 1,
        // 3
        ASSERT_EQ(0, *(int *) sll->head->val);
        ASSERT_EQ(1, *(int *) sll->head->next->val);
        ASSERT_EQ(0, *(int *) inserted_after->val);
        ASSERT_EQ(3, sll->len);

        SLL_clean(sll);
        free(sll);
    }

    TEST(SLL_Tests, SLL_Insert) {
        SLL *sll;
        for (auto &num_vec : num_vecs) {
            sll = SLL_create();
            POPULATE_LL(sll, num_vec, &SLL_insert);

            SLL_Node *node = sll->head;
            int idx = (int) num_vec.size() - 1;
            while (node) {
                ASSERT_GT(idx, -1);  // Prevent accidental infinite loop
                ASSERT_EQ(*(int *) node->val, num_vec.at(idx));
                node = node->next;
                idx--;
            }
        }
        free(sll);
    }

    TEST(SLL_Tests, SLL_Delete_first) {
        SLL *sll;
        for (auto &num_vec : num_vecs) {
            sll = SLL_create();

            // Test SLL_remove_first on an empty SLL
            SLL_remove_first(sll);
            ASSERT_EMPTY_SLL(sll);

            POPULATE_LL(sll, num_vec, &SLL_insert);

            SLL_Node *node;
            int idx{(int) num_vec.size() - 1};
            while (sll->head) {
                ASSERT_GT(idx, -1);  // Prevent accidental infinite loop
                node = SLL_remove_first(sll);
                ASSERT_EQ(*(int *) node->val, num_vec.at(idx));
                ASSERT_EQ(sll->head, node->next);
                ASSERT_EQ(sll->len, idx);
                free(node);
                idx--;
            }
            SLL_clean(sll);
            free(sll);
        }
    }

    TEST(SLL_Tests, SLL_Clean) {
        SLL *sll = SLL_create();

        // Test cleaning an empty SLL
        SLL_clean(sll);
        ASSERT_EMPTY_SLL(sll);
        free(sll);

        for (auto &num_vec : num_vecs) {
            sll = SLL_create();
            POPULATE_LL(sll, num_vec, &SLL_insert);
            SLL_clean(sll);
            ASSERT_EMPTY_SLL(sll);
            free(sll);
        }
    }
} // namespace SLL_Gtests

#pragma clang diagnostic pop
