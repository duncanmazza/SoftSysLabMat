/* Matrix data structure implementation
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#ifndef SOFTSYSSOFTSYSLABMAT_MATRIX_H
#define SOFTSYSSOFTSYSLABMAT_MATRIX_H

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

void print_matrix(matrix *mat);

void complete_matrix(matrix *mat, float input[][3], int row, int col);\

matrix *add_int(matrix *mat, float k);

matrix *add_matrix(matrix *mat1, matrix *mat2);

#ifdef __cplusplus
}
#endif

#endif //SOFTSYSSOFTSYSLABMAT_MATRIX_H
