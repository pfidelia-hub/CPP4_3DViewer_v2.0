#pragma once

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-7

namespace s21 {



enum class matrix_type_t {
  CORRECT_MATRIX = 0,
  INCORRECT_MATRIX = 1,
  IDENTITY_MATRIX = 2,
  ZERO_MATRIX = 3
};

struct matrix_t {
  double **matrix = nullptr;
  int rows;
  int columns;
  matrix_type_t matrix_type;
};

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);
double **dynamic_array_alloc(int rows, int columns);
void assign_matrix(matrix_t *A, ...);
int update_type(matrix_t *A);
int check_correctness(matrix_t *A);
#define SUCCESS 1
#define FAILURE 0

#if FLAG == 99
int s21_eq_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_mult_number(matrix_t *A, double number);
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_transpose(matrix_t *A);
matrix_t s21_calc_complements(matrix_t *A);
double s21_determinant(matrix_t *A);
matrix_t s21_inverse_matrix(matrix_t *A);

/*----------------------secondary functions---------------------------*/

matrix_type_t check_matrix_type(matrix_t *A);
matrix_t minor_matrix(matrix_t *A, int sub_i, int sub_j);

void pr_matrix(matrix_t a);
#endif

}  //  namespace s21
