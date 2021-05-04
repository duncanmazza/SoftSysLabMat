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


char *matrix_str_repr(const matrix *const mat) {
    SLL *sll = SLL_create();
    SLL_Node *node = sll->head;

    for (int x = 0; x < mat->rows; x++) {
        node = SLL_insert_after(sll, format_msg("%c", CTYPE_CHAR, 0, 1,
                                         x == 0 ? '[' : ' '), node);
        for (int y = 0; y < mat->column; y++) {
            node = SLL_insert_after(sll, format_msg("%g", CTYPE_CHAR, 1, 1,
                                             mat->data[x][y]), node);
            if (y != mat->column - 1) {
                node = SLL_insert_after(sll, format_msg("%c", CTYPE_CHAR, 0, 1,
                                                 ' '), node);
            } else {
                if (x != mat->rows - 1)
                    node = SLL_insert_after(sll, format_msg("%c", CTYPE_CHAR, 0, 1,
                                                     '\n'), node);
            }
        }
    }
    SLL_insert_after(sll, format_msg("%s", CTYPE_STR, 0, 1,
                                     "]"), node);

    char *mat_repr = sll_strs_to_str(sll, "", "");
    SLL_clean(sll);
    free(sll);
    return mat_repr;
}


void print_matrix(const matrix *const mat) {
    char *mat_repr = matrix_str_repr(mat);
    printf("%s\n", mat_repr);
    free(mat_repr);
}


int complete_matrix(matrix *mat, const float *input, int row, int col) {
    if (mat->rows != row || mat->column != col) {
        fprintf(stderr, "Specified rows and columns of input array "
                        "do not match the matrix dimensions");
        return 0;
    }
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            mat->data[i][j] = input[col * i + j];
        }
    }
    return 1;
}


matrix *matrix_add_scalar(matrix *mat, float k) {
    matrix *total = make_matrix(mat->rows, mat->column);
    for (int x = 0; x < mat->rows; x++) {
        for (int y = 0; y < mat->column; y++) {
            total->data[x][y] = mat->data[x][y] + k;
        }
    }
    return total;
}


matrix *matrix_add(matrix *mat1, matrix *mat2) {
    if (mat1->rows != mat2->rows && mat1->column != mat2->column) {
        return NULL;
    }
    matrix *total = make_matrix(mat1->rows, mat1->column);
    for (int x = 0; x < total->rows; x++) {
        for (int y = 0; y < total->column; y++) {
            total->data[x][y] = mat1->data[x][y] + mat2->data[x][y];
        }
    }
    return total;
}


matrix *matrix_sub(matrix *mat1, matrix *mat2) {
    if (mat1->rows != mat2->rows && mat1->column != mat2->column) {
        return NULL;
    }
    matrix *total = make_matrix(mat1->rows, mat1->column);
    for (int x = 0; x < total->rows; x++) {
        for (int y = 0; y < total->column; y++) {
            total->data[x][y] = mat1->data[x][y] - mat2->data[x][y];
        }
    }
    return total;
}


matrix *matrix_multiply(matrix *mat1, matrix *mat2) {
    if (mat1->column != mat2->rows) {
      return 0;
    }
    matrix *product = make_matrix(mat1->rows, mat2->column);
    for (int x = 0; x < product->rows; x++) {
        for (int y = 0; y < product->column; y++) {
          for (int z = 0; z < mat1 ->column; z++) {
              product->data[x][y] += mat1->data[x][z] * mat2->data[z][y];
          }
        }
    }
    return product;
}


matrix *matrix_multiply_scalar(matrix *mat, float k) {
    matrix *total = make_matrix(mat->rows, mat->column);
    for (int x = 0; x < mat->rows; x++) {
        for (int y = 0; y < mat->column; y++) {
            total->data[x][y] = mat->data[x][y] * k;
        }
    }
    return total;
}

/*
int main() {
    int i = 3;
    int j = 3;
    matrix *mat1 = make_matrix(i, j);
    float cell[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    //mat = add(mat, i);
    complete_matrix(mat1, (const float *) cell, i, j);
    matrix *mat2 = make_matrix(i,j);
    //float cell[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    //mat1 = add_int(mat1, i);
    //complete_matrix(mat2, cell, i, j);
    //matrix *sum = add_matrix(mat1, mat2);
    print_matrix(mat1);
    return 0;
}
*/
