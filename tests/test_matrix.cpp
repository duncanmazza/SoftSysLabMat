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
#define ASSERT_EMPTY_MATRIX(mat) ({                                            \
    ASSERT_EQ((mat)->rows, 0);                                                 \
    ASSERT_EQ((mat)->column, 0);                                               \
})

    TEST(MAT_Tests, MAT_Create) {
        int i = 0;
        int j = 0;
        matrix *mat = make_matrix(0, 0);
        ASSERT_EMPTY_MATRIX(mat);
        free(mat);
    }

    TEST(MAT_Tests, MAT_Complete_Matrix) {
        int i = 2;
        int j = 3;
        matrix* mat = make_matrix(i,j);
        float test[] = {1,2,3,4,5,6};
        complete_matrix(mat, test, i, j);

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

    TEST(MAT_Tests, MAT_add_int_1) {
      int i = 2;
      int j = 3;
      matrix* mat = make_matrix(i,j);
      float test[] = {1,2,3,4,5,6};
      complete_matrix(mat, test, i, j);
      matrix *sum = matrix_add_scalar(mat, 3);
      ASSERT_EQ(sum->data[0][0], 4);
      ASSERT_EQ(sum->data[0][1], 5);
      ASSERT_EQ(sum->data[0][2], 6);
      ASSERT_EQ(sum->data[1][0], 7);
      ASSERT_EQ(sum->data[1][1], 8);
      ASSERT_EQ(sum->data[1][2], 9);
      ASSERT_EQ(sum->rows, i);
      ASSERT_EQ(sum->column, j);
      free(mat);
      free(sum);
    }

    TEST(MAT_Tests, MAT_add_matrix) {
      int i = 2;
      int j = 3;
      matrix* mat1 = make_matrix(i,j);
      float test[] = {1,2,3,4,5,6};
      matrix* mat2 = make_matrix(i,j);
      complete_matrix(mat1, test, i, j);
      complete_matrix(mat2, test, i, j);
      matrix *sum = matrix_add(mat1, mat2);
      ASSERT_EQ(sum->data[0][0], 2);
      ASSERT_EQ(sum->data[0][1], 4);
      ASSERT_EQ(sum->data[0][2], 6);
      ASSERT_EQ(sum->data[1][0], 8);
      ASSERT_EQ(sum->data[1][1], 10);
      ASSERT_EQ(sum->data[1][2], 12);
      ASSERT_EQ(sum->rows, i);
      ASSERT_EQ(sum->column, j);
      free(mat1);
      free(mat2);
      free(sum);
    }

    TEST(MAT_Tests, MAT_multiply_matrix) {
      int i = 2;
      int j = 2;
      int a = 2;
      int b = 1;
      matrix* mat1 = make_matrix(i,j);
      float test1[] = {1,1,1,1};
      matrix* mat2 = make_matrix(a,b);
      float test2[] = {1,1};
      complete_matrix(mat1, test1, i, j);
      complete_matrix(mat2, test2, a, b);
      matrix *product = matrix_multiply(mat1, mat2);
      ASSERT_EQ(product->data[0][0], 2);
      ASSERT_EQ(product->data[1][0], 2);
      ASSERT_EQ(product->rows, i);
      ASSERT_EQ(product->column, b);
      free(mat1);
      free(mat2);
      free(product);
    }

    TEST(MAT_Tests, MAT_multiply_scalar) {
      int i = 3;
      int j = 1;
      matrix* mat1 = make_matrix(i,j);
      float test1[] = {1,1,1};
      complete_matrix(mat1, test1, i, j);
      float scal = 3;
      matrix *product = matrix_multiply_scalar(mat1, scal);
      ASSERT_EQ(product->data[0][0], 3);
      ASSERT_EQ(product->data[1][0], 3);
      ASSERT_EQ(product->data[2][0], 3);
      ASSERT_EQ(product->rows, i);
      ASSERT_EQ(product->column, j);
      free(mat1);
      free(product);
    }

} // namespace SLL_Gtests

#pragma clang diagnostic pop
