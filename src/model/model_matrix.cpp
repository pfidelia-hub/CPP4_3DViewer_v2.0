#include "model_matrix.h"

namespace s21 {



matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t A;
  if (rows > 0 && columns > 0) {
    A.matrix = dynamic_array_alloc(rows, columns);
    A.matrix_type = matrix_type_t::ZERO_MATRIX;
    A.rows = rows;
    A.columns = columns;
  } else {
    A.matrix = NULL;
    A.rows = 0;
    A.columns = 0;
    A.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  }
  return A;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = 0;
    }
  }
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->matrix_type = matrix_type_t::INCORRECT_MATRIX;
}

double **dynamic_array_alloc(int rows, int columns) {
    double **matrix = new double* [rows];
  for (int i = 0; i < rows; i++) {
    matrix[i] = new double[columns];
  }
  return matrix;
}

int check_correctness(matrix_t *A) {
  int flag = FAILURE;
  if (A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    flag = SUCCESS;
    for (int row = 0; row < A->rows && flag; row++) {
      for (int col = 0; col < A->columns && flag; col++) {
        if (isnan(A->matrix[row][col]) || isinf(A->matrix[row][col])) {
          flag = FAILURE;
        }
      }
    }
  }
  return flag;
}

int update_type(matrix_t *A) {
  int res = check_correctness(A) ? (int)matrix_type_t::CORRECT_MATRIX : (int)matrix_type_t::INCORRECT_MATRIX;
  if (res == (int)matrix_type_t::CORRECT_MATRIX) {
    int flag_1 = 1, flag_0 = 1;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (A->matrix[i][j] != 0)
          flag_0 = 0;
        if (i == j && A->matrix[i][j] != 1)
          flag_1 = 0;
        if (i != j && A->matrix[i][j] != 0)
          flag_1 = 0;
      }
    }
    if (A->rows != A->columns)
      flag_1 = 0;
    if (flag_0)
      res = (int)matrix_type_t::ZERO_MATRIX;
    else if (flag_1)
      res = (int)matrix_type_t::IDENTITY_MATRIX;
  }
  A->matrix_type = (matrix_type_t)res;
  return res;
}

void assign_matrix(matrix_t *A, ...) {
  va_list data;
  va_start(data, A);
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      A->matrix[row][col] = va_arg(data, double);
    }
  }
  va_end(data);
  update_type(A);
}

#if FLAG == 99

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX ||
      B->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result = FAILURE;
  } else if (A->matrix_type != B->matrix_type) {
    result = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows && result != FAILURE; i++) {
      for (int j = 0; j < A->columns && result != FAILURE; j++) {
        if ((A->matrix[i][j] + EPS) <= B->matrix[i][j] ||
            (A->matrix[i][j] - EPS) >= B->matrix[i][j]) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
  matrix_t result = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX ||
      B->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
    result.matrix_type = check_matrix_type(&result);
  }
  return result;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
  matrix_t result = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX ||
      B->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
    result.matrix_type = check_matrix_type(&result);
  }
  return result;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
  matrix_t result = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (isnan(number) || isinf(number)) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (number != 0) {
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    result.matrix_type = check_matrix_type(&result);
  }
  return result;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
  matrix_t result = s21_create_matrix(A->rows, B->columns);
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX ||
      B->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->matrix_type != matrix_type_t::ZERO_MATRIX && B->matrix_type != matrix_type_t::ZERO_MATRIX) {
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
    result.matrix_type = check_matrix_type(&result);
  }
  return result;
}

matrix_t s21_transpose(matrix_t *A) {
  matrix_t result = s21_create_matrix(A->columns, A->rows);
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->matrix_type != matrix_type_t::ZERO_MATRIX) {
    for (int i = 0; i < result.rows; i++) {
      for (int j = 0; j < result.columns; j++) {
        result.matrix[i][j] = A->matrix[j][i];
      }
    }
    result.matrix_type = check_matrix_type(&result);
  }
  return result;
}

matrix_t s21_calc_complements(matrix_t *A) {
  matrix_t result = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->matrix_type == matrix_type_t::ZERO_MATRIX) {
    result.matrix_type = matrix_type_t::ZERO_MATRIX;
  } else if (A->matrix_type == matrix_type_t::IDENTITY_MATRIX && A->rows != 1) {
    result.matrix_type = matrix_type_t::ZERO_MATRIX;
  } else {
    if (A->rows == 1) {
      result.matrix[0][0] = A->matrix[0][0];
    } else if (A->rows > 1) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor = minor_matrix(A, i, j);
          double determinant_minor = s21_determinant(&minor);
          result.matrix[i][j] = pow((-1), i + j) * determinant_minor;
          s21_remove_matrix(&minor);
        }
      }
    }
    result.matrix_type = check_matrix_type(&result);
  }
  return result;
}

double s21_determinant(matrix_t *A) {
  double determinant = 0;
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    determinant = NAN;
  } else if (A->rows != A->columns) {
    determinant = NAN;
  } else if (A->matrix_type == matrix_type_t::ZERO_MATRIX) {
    determinant = 0;
  } else if (A->matrix_type == matrix_type_t::IDENTITY_MATRIX && A->rows > 1) {
    determinant = 0;
  } else {
    if (A->rows == 1) {
      determinant = A->matrix[0][0];
    } else if (A->rows == 2) {
      determinant = A->matrix[0][0] * A->matrix[1][1] -
                    (A->matrix[1][0] * A->matrix[0][1]);
    } else if (A->rows > 2) {
      int sign = 1;
      for (int i = 0; i < A->rows; i++) {
        matrix_t minor = minor_matrix(A, i, 0);
        determinant += sign * A->matrix[i][0] * s21_determinant(&minor);
        sign *= -1;
        s21_remove_matrix(&minor);
      }
    }
  }
  return determinant;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
  matrix_t result = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == matrix_type_t::INCORRECT_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->matrix_type == matrix_type_t::ZERO_MATRIX) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else if (A->matrix_type == matrix_type_t::IDENTITY_MATRIX && A->rows != 1) {
    result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
  } else {
    double determinant = s21_determinant(A);
    if (determinant != 0 && !isnan(determinant)) {
      double number = 1. / determinant;
      if (A->rows == 1) {
        result.matrix[0][0] = number;
        result.matrix_type = check_matrix_type(&result);
      } else {
        matrix_t algebraic_complement = s21_calc_complements(A);
        matrix_t transpose_algebraic = s21_transpose(&algebraic_complement);
        s21_remove_matrix(&result);
        result = s21_mult_number(&transpose_algebraic, number);
        s21_remove_matrix(&algebraic_complement);
        s21_remove_matrix(&transpose_algebraic);
      }
    } else {
      result.matrix_type = matrix_type_t::INCORRECT_MATRIX;
    }
  }
  return result;
}



matrix_type_t check_matrix_type(matrix_t *A) {
  matrix_type_t type;
  if (A->matrix[0][0] == 0) {
    type = matrix_type_t::ZERO_MATRIX;
    for (int i = 0; i < A->rows && type == matrix_type_t::ZERO_MATRIX; i++) {
      for (int j = 0; j < A->columns && type == matrix_type_t::ZERO_MATRIX; j++) {
        if (A->matrix[i][j] != 0) {
          type = matrix_type_t::CORRECT_MATRIX;
        }
      }
    }
  } else if (A->matrix[0][0] == 1) {
    type = matrix_type_t::IDENTITY_MATRIX;
    for (int i = 0; i < A->rows && type == matrix_type_t::IDENTITY_MATRIX; i++) {
      for (int j = 0; j < A->columns && type == matrix_type_t::IDENTITY_MATRIX; j++) {
        if (A->matrix[i][j] != 1) {
          type = matrix_type_t::CORRECT_MATRIX;
        }
      }
    }
  } else {
    type = matrix_type_t::CORRECT_MATRIX;
  }
  return type;
}

matrix_t minor_matrix(matrix_t *A, int sub_i, int sub_j) {
  matrix_t minor = s21_create_matrix(A->rows - 1, A->columns - 1);
  int flag_i = 0;
  for (int i = 0; i < minor.rows; i++) {
    int flag_j = 0;
    if (i == sub_i && !flag_i) {
      flag_i = 1;
    }
    for (int j = 0; j < minor.columns; j++) {
      if (j == sub_j && !flag_j) {
        flag_j = 1;
      }
      minor.matrix[i][j] = A->matrix[i + flag_i][j + flag_j];
    }
  }
  minor.matrix_type = check_matrix_type(&minor);
  return minor;
}

void pr_matrix(matrix_t a) {
  if (a.matrix_type != matrix_type_t::INCORRECT_MATRIX) {
    if (a.matrix_type == matrix_type_t::CORRECT_MATRIX)
      printf("matrix_type_t::CORRECT_MATRIX\n");
    else if (a.matrix_type == matrix_type_t::IDENTITY_MATRIX)
      printf("matrix_type_t::IDENTITY_MATRIX\n");
    else if (a.matrix_type == matrix_type_t::ZERO_MATRIX)
      printf("matrix_type_t::ZERO_MATRIX\n");
    for (int i = 0; i < a.rows; i++) {
      for (int j = 0; j < a.columns; j++) {
        printf("[ %.2lf ] ", a.matrix[i][j]);
        if (j == a.columns - 1)
          printf("\n");
      }
    }
  } else {
    printf("matrix_type_t::INCORRECT_MATRIX\n");
  }
  printf("D = %lf\n", s21_determinant(&a));
}

#endif

}  //  namespace s21
