/* Matrix data structure implementation
 *
 * Duncan and Junwon LabMat SoftSys Project 1
 *
 */

#include "../include/matrix.h"


matrix *make_matrix(int row, int col) {
    struct matrix *mat = malloc(sizeof(matrix));
    mat->rows = row;
    mat->column = col;
    mat->data = (float **) malloc(sizeof(float *) * row);
    int k;
    for (k = 0; k < row; k++) {
        mat->data[k] = (float *) malloc(sizeof(float *) * col);
    }
    return mat;
}


void print_matrix(matrix *mat) {
    for (int x = 0; x < mat->rows; x++) {
        for (int y = 0; y < mat->column; y++) {
            printf("%f \n", mat->data[x][y]);
        }
    }
}


void complete_matrix(matrix *mat, float (*input)[3], int row, int col) {

    if (mat->rows != row || mat->column != col) {
        printf("nothing");
        return;
    }
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            mat->data[i][j] = input[i][j];
            //printf("%f", input[i+j]);
        }
    }
    //return mat;
}


matrix *add_int(matrix *mat, float k) {
    matrix *total = make_matrix(mat->rows, mat->column);
    for (int x = 0; x < mat->rows; x++) {
        for (int y = 0; y < mat->column; y++) {
            total->data[x][y] = mat->data[x][y] + k;
        }
    }
    return total;
}


matrix *add_matrix(matrix *mat1, matrix *mat2) {
    if (mat1->rows != mat2->rows && mat1->column != mat2->column) {
        return 0;
    }
    matrix *total = make_matrix(mat1->rows, mat1->column);
    for (int x = 0; x < total->rows; x++) {
        for (int y = 0; y < total->column; y++) {
            total->data[x][y] = mat1->data[x][y] + mat2->data[x][y];
        }
    }
    return total;
}

//int main() {
//  int i = 3;
//  int j = 3;
//  matrix *mat1 = make_matrix(i, j);
//  float cell[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
//  //mat = add(mat, i);
//  complete_matrix(mat1, cell, i, j);
//  matrix *mat2 = make_matrix(i,j);
//  //float cell[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
//  mat1 = add_int(mat1, i);
//  //complete_matrix(mat2, cell, i, j);
//  //matrix *sum = add_matrix(mat1, mat2);
//  print_matrix(mat1);
//  return 0;
//}
