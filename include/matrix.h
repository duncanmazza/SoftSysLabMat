/* Matrix data structure implementation
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_MATRIX_H
#define SOFTSYSSOFTSYSLABMAT_MATRIX_H

#include "sll.h"
#include "str_utils.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct matrix {
    int rows;
    int cols;
    float **data;
} matrix;


matrix *make_matrix(int row, int col);

void print_matrix(const matrix *mat);

/** Fills out the values of a matrix
 *
 * @param mat Matrix to populate
 * @param input Flattened array representing the 2d matrix
 * @param row Number of rows represented in the input array
 * @param col Number of columns represented in the input array
 * @return 0 if dimensions do not match and 1 if they do
 */
int complete_matrix(matrix *mat, const float *input, int row, int col);

matrix *matrix_add_scalar(matrix *mat, float k);

matrix *matrix_add(matrix *mat1, matrix *mat2);

matrix *matrix_sub(matrix *mat1, matrix *mat2);

char *matrix_str_repr(const matrix *mat);

matrix *matrix_multiply(matrix *mat1, matrix *mat2);

matrix *matrix_multiply_scalar(matrix *mat, float k);

matrix *matrix_transpose(matrix *mat);

void matrix_free(matrix *mat);

/** Checks whether the matrices have equivalent dimensions.
 *
 * @return 1 if matrix dimensions match and 0 otherwise. If any null values are
 *  encountered, 0 is returned.
 */
int matrix_dims_eq(matrix *m1, matrix* m2);

#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_MATRIX_H
