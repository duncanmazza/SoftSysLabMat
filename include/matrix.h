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
    int rows, column;
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

char *matrix_str_repr(const matrix *mat);

matrix *multiply_matrix(matrix *mat1, matrix *mat2);

#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_MATRIX_H
