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

#include "../include/matrix.h"
#include "test_all.hpp"


namespace MATRIX_Gtests {
#define ASSERT_EMPTY_MATRIX(mat) ({                                               \
    ASSERT_EQ((mat)->rows, 0);                                                  \
    ASSERT_EQ((mat)->column, 0)
})

    NUM_VECS  // Create the num_vecs variable

    TEST(MAT_Tests, MAT_Create) {
        int i = 0;
        int j = 0;
        matrix *mat = make_matrix(0, 0);
        ASSERT_EMPTY_MATRIX(mat);
        free(mat);
    }

    TEST(MAT_Tests, MAT_Complete_Matrix) {
        // Create SLL with integers in the order: 1, 2, 3
        int i = 2;
        int j = 3;
        matrix* mat = make_matrix(i,j);
        float test[] = {1,2,3,4,5,6};
        complete_matrix(mat, test, i, j);

        // Check that the SLL was updated correctly
        ASSERT_EQ(mat->data[0][0], 1);
        ASSERT_EQ(mat->data[0][1], 2);
        ASSERT_EQ(mat->data[0][2], 3);
        ASSERT_EQ(mat->data[1][0], 4);
        ASSERT_EQ(mat->data[1][1], 5);
        ASSERT_EQ(mat->data[1][2], 6);
        ASSERT_EQ(mat->rows, i);
        ASSERT_EQ(mat->column, j);
        free(mat);
    }

    TEST(MAT_Tests, MAT_add_int) {
      int i = 2;
      int j = 3;
      matrix* mat = make_matrix(i,j);
      float test[] = {1,2,3,4,5,6};
      complete_matrix(mat, test, i, j);
      matrix *sum = add_int(mat, 3);
      ASSERT_EQ(mat->data[0][0], 4);
      ASSERT_EQ(mat->data[0][1], 5);
      ASSERT_EQ(mat->data[0][2], 6);
      ASSERT_EQ(mat->data[1][0], 7);
      ASSERT_EQ(mat->data[1][1], 8);
      ASSERT_EQ(mat->data[1][2], 9);
      ASSERT_EQ(mat->rows, i);
      ASSERT_EQ(mat->column, j);
      free(mat);
    }

    TEST(MAT_Tests, MAT_add_int) {
      int i = 2;
      int j = 3;
      matrix* mat = make_matrix(i,j);
      float test[] = {1,2,3,4,5,6};
      complete_matrix(mat, test, i, j);
      matrix *sum = add_int(mat, 3);
      ASSERT_EQ(mat->data[0][0], 4);
      ASSERT_EQ(mat->data[0][1], 5);
      ASSERT_EQ(mat->data[0][2], 6);
      ASSERT_EQ(mat->data[1][0], 7);
      ASSERT_EQ(mat->data[1][1], 8);
      ASSERT_EQ(mat->data[1][2], 9);
      ASSERT_EQ(mat->rows, i);
      ASSERT_EQ(mat->column, j);
      free(mat);
    }


} // namespace SLL_Gtests

#pragma clang diagnostic pop