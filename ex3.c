#include "ex3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAT_ALLOC_ERR "ERROR: calloc - "\
                              "matrix memory allocation failed."

#define MAT_DATA_ALLOC_ERR "ERROR: calloc - "\
                                  "matrix data memory allocation failed."

#define INDEX_ERR "ERROR: Invalid index "\
                              "provided - Index out of matrix range.\n"

#define NULL_DATA_SLICE_ERR "ERROR: Matrix"\
                              " data is NULL - Cannot slice matrix.\n"

#define INCOMPATIBLE_COL_ERR "ERROR: Incompatible "\
                              "columns number for adding matrix vertically.\n"

#define INCOMPATIBLE_ROWS_ERR "ERROR: Incompatible rows \n"\
                              "number for adding matrix horizontally.\n"

#define NULL_DATA_RAVEL_ERR "ERROR: Matrix data is NULL - Cannot ravel matrix.\n"

/**
 * create a new matrix_s on the heap.
 * @param n_rows number of rows in the new matrix_s.
 * @param n_columns number of columns in the new matrix_s.
 * @return A pointer to the new matrix_s struct.
 */
matrix *create_matrix(size_t n_rows, size_t n_columns) {
    matrix *new_matrix = malloc(sizeof(matrix));
    new_matrix->data = NULL;
    matrix *tmp_matrix = new_matrix;
    double **matrix_data = NULL;
    double **tmp_data = NULL;
    if (tmp_matrix == NULL)
    {
        fprintf(stderr, "%s", MAT_ALLOC_ERR);
        return NULL;
    }
    else if (n_rows == 0 || n_columns == 0) {
        new_matrix->data = NULL;
        new_matrix->n_rows = 0;
        new_matrix->n_columns = 0;
        return new_matrix;
    } else {
        matrix_data = calloc((int) n_rows, sizeof(double *));
        tmp_data = matrix_data;
        if (tmp_data == NULL) {
            fprintf(stderr, "%s", MAT_DATA_ALLOC_ERR);
            free(new_matrix);
//            free_matrix(new_matrix);
            return NULL;
        }
        for (int i = 0; i < (int) n_rows; i++) {
            matrix_data[i] = calloc((int) n_columns, sizeof(double));
            tmp_data[i] = matrix_data[i];
            if (tmp_data[i] == NULL) {
                fprintf(stderr, "%s", MAT_DATA_ALLOC_ERR);
//                free_matrix(new_matrix);
                for(int j = 0; j < i; j++){
                    free(matrix_data[j]);
                    matrix_data[j] = NULL;
                }
                free(matrix_data);
                matrix_data = NULL;
                free(new_matrix);
                matrix_data = NULL;
                return NULL;
            }
        }
        new_matrix->data = matrix_data;
        new_matrix->n_rows = n_rows;
        new_matrix->n_columns = n_columns;
    }
    return new_matrix;
}

/**
 * Get value based on index.
 * @param mat A matrix type.
 * @param row_index index of the row.
 * @param col_index index of the column.
 * @return matrix_s[row_index, col_index],
 * NULL if the index is out of range.
 */
double *get_by_index(matrix *mat, size_t row_index, size_t col_index) {
    if ((row_index >= mat->n_rows) || (col_index >= mat->n_columns)) {
        fprintf(stderr, "%s", INDEX_ERR);
        return NULL;
    }
    double *index = &mat->data[row_index][col_index];
    return index;
}

/**
 * Copy matrix data from one matrix to another (not addresses but actual data!)
 * @param mat matrix to copy from.
 * @return mat_copy - a matrix with the copied data.
 */
matrix *copy_mat_data(matrix *mat) {
    size_t copy_rows = mat->n_rows;
    size_t copy_cols = mat->n_columns;
    matrix *mat_copy = create_matrix(copy_rows, copy_cols);
    if (mat_copy == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < copy_rows; i++) {
        for (size_t j = 0; j < copy_cols; j++) {
            mat_copy->data[i][j] = mat->data[i][j];
        }
    }
    return mat_copy;
}

/**
 * Slice a matrix - get a "slice" of a given matrix.
 * @param mat A matrix type.
 * @param row_start index to start the slice for rows
 * (includes the start index in slice).
 * @param row_end index to end the slice for rows
 * (doesn't include the end index in slice).
 * @param col_start index to start the slice for columns
 * (includes the start index in slice).
 * @param col_end index to end the slice for cols
 * (doesn't include the end index in slice).
 * @return A sliced matrix according to the demands on the exercise's
 * instructions.
 */
matrix *slice(matrix *mat, size_t row_start,
              size_t row_end, size_t col_start, size_t col_end) {
    size_t n_col_num;
    size_t n_row_num;
    if (col_end >= mat->n_columns) {
        col_end = mat->n_columns;
    }
    if (row_end >= mat->n_rows) {
        row_end = mat->n_rows;
    }
    n_col_num = col_end - col_start;
    n_row_num = row_end - row_start;
    if (mat->data == NULL || mat->n_rows == 0 || mat->n_columns == 0) {
        fprintf(stderr, "%s", NULL_DATA_SLICE_ERR);
        return NULL;
    } else if (row_start > row_end || col_start > col_end) {
        matrix *empty_sliced_mat = create_matrix(0, 0);
        return empty_sliced_mat;
    }
    int n = -1;
    matrix *sliced_mat = create_matrix((int) n_row_num, (int) n_col_num);
    if (sliced_mat == NULL)
    {
        return NULL;
    }
    for (int i = (int) row_start; i < (int) row_end; ++i) {
        n++;
        int m = 0;
        for (int j = (int) col_start; j < (int) col_end; ++j) {
            sliced_mat->data[n][m] = mat->data[i][j];
            m++;
        }
    }
    return sliced_mat;
}

/**
 * Concatenate vertically 2 given matrices.
 * @param top a matrix that will be the top matrix
 * after concatenate vertically.
 * @param bottom a matrix that will be the bottom matrix
 * after concatenate vertically.
 * @return A concatenated vertically matrix which combines both matrices.
 */
matrix *concatenate_vertically(matrix *top, matrix *bottom) {
    if (top->data == NULL && bottom->data == NULL) {
        matrix *empty_mat = create_matrix(0, 0);
        return empty_mat;
    } else if (bottom->data == NULL) {
        matrix *top_copy = copy_mat_data(top);
        return top_copy;
    } else if (top->data == NULL) {
        matrix *bottom_copy = copy_mat_data(bottom);
        return bottom_copy;
    } else if (top->n_columns != bottom->n_columns) {
        fprintf(stderr, "%s", INCOMPATIBLE_COL_ERR);
        return NULL;
    }
    size_t vertical_rows = bottom->n_rows + top->n_rows;
    matrix *vertical_matrix = create_matrix(vertical_rows, top->n_columns);
    if (vertical_matrix == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < top->n_rows; ++i) {
        for (size_t j = 0; j < top->n_columns; ++j) {
            vertical_matrix->data[i][j] = top->data[i][j];
        }
    }
    for (size_t m = top->n_rows; m < bottom->n_rows + top->n_rows; ++m) {
        for (size_t n = 0; n < bottom->n_columns; ++n) {
            vertical_matrix->data[m][n] = bottom->data[m - top->n_rows][n];
        }
    }
    return vertical_matrix;
}

/**
 * Concatenate horizontally 2 given matrices.
 * @param left a matrix that will be the left matrix
 * after concatenate horizontally.
 * @param right a matrix that will be the right matrix
 * after concatenate horizontally.
 * @return A concatenated horizontally matrix which combines both matrices.
 */
matrix *concatenate_horizontally(matrix *left, matrix *right) {
    if (left->data == NULL && right->data == NULL) {
        matrix *empty_mat = create_matrix(0, 0);
        return empty_mat;
    } else if (left->data == NULL) {
        matrix *right_copy = copy_mat_data(right);
        return right_copy;
    } else if (right->data == NULL) {
        matrix *left_copy = copy_mat_data(left);
        return left_copy;
    } else if (left->n_rows != right->n_rows) {
        fprintf(stderr, "%s", INCOMPATIBLE_ROWS_ERR);
        return NULL;
    }
    size_t horizontal_cols = left->n_columns + right->n_columns;
    matrix *horizontal_matrix = create_matrix(left->n_rows, horizontal_cols);
    if (horizontal_matrix == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < left->n_rows; ++i) {
        for (size_t j = 0; j < left->n_columns; ++j) {
            horizontal_matrix->data[i][j] = left->data[i][j];
        }
    }
    for (size_t m = 0; m < right->n_rows; ++m) {
        for (size_t n = left->n_columns;
             n < left->n_columns + right->n_columns; ++n) {
            horizontal_matrix->data[m][n] = right->data[m][n -
                                                           left->n_columns];
        }
    }
    return horizontal_matrix;
}

/**
 * Transpose a given matrix.
 * @param mat Matrix to preform transpose.
 * @return A transposed matrix.
 */
matrix *transpose(matrix *mat) {
    size_t transposed_rows = mat->n_columns;
    size_t transposed_cols = mat->n_rows;
    if (mat->data == NULL) {
        matrix *transposed_mat = create_matrix(transposed_rows,
                                               transposed_cols);
        return transposed_mat;
    }
    matrix *transposed_mat = create_matrix(transposed_rows, transposed_cols);
    if (transposed_mat == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < transposed_rows; i++) {
        for (size_t j = 0; j < transposed_cols; j++) {
            transposed_mat->data[i][j] = mat->data[j][i];
        }
    }
    return transposed_mat;
}

/**
 * @param mat a matrix to preform ravel on.
 * @return an array of doubles containing the rows of the matrix 1 by 1
 * in a row from top to bottom row.
 */
double *ravel(matrix *mat) {
    if (mat->data == NULL) {
        fprintf(stderr, "%s", NULL_DATA_RAVEL_ERR);
        return NULL;
    }
    double *mat_array = calloc((mat->n_columns) * (mat->n_rows),
                               sizeof(double));
    int index = -1;
    for (size_t i = 0; i < mat->n_rows; i++) {
        for (size_t j = 0; j < mat->n_columns; j++) {
            index++;
            mat_array[index] = mat->data[i][j];
        }
    }
    return mat_array;
}

/**
 * Free matrix columns data, rows data and the matrix struct itself.
 * @param mat A matrix to free.
 * @return Doesn't return anything.
 */
void free_matrix(matrix *mat) {
    for (size_t i = 0; i < mat->n_rows; i++) {
        double *tmp_col_data = mat->data[i];
        if (tmp_col_data != NULL) {
            free(mat->data[i]);
            mat->data[i] = NULL;
        }
    }
    free(mat->data);
    mat->data = NULL;
    free(mat);
    mat = NULL;
}

