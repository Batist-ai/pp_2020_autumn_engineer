// Copyright 2020 Boytsov Vladislav
#ifndef MODULES_TASK_1_BOYTSOV_V_MATRIX_ROWS_SUM_MATRIX_ROWS_SUM_H_
#define MODULES_TASK_1_BOYTSOV_V_MATRIX_ROWS_SUM_MATRIX_ROWS_SUM_H_

#include <vector>

std::vector<std::vector<int> > createRandomMatrix(const int M, const int N);
std::vector<int> getSequentialSumOfRows(const std::vector<int> vec, const int M, const int N);
std::vector<int> matrixToVector(std::vector<std::vector<int> > mat);
std::vector<int> getParallelSumOfRows(const std::vector<std::vector<int> > mat, const int M, const int N);

#endif  // MODULES_TASK_1_BOYTSOV_V_MATRIX_ROWS_SUM_MATRIX_ROWS_SUM_H_
