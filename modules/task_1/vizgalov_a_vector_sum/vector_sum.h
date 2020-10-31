// Copyright 2020 Vizgalov Anton
#ifndef MODULES_TASK_1_VIZGALOV_A_VECTOR_SUM_VECTOR_SUM_H_
#define MODULES_TASK_1_VIZGALOV_A_VECTOR_SUM_VECTOR_SUM_H_

#include <vector>

std::vector<int> getRandomVector(int size);
int getVectorSumSequential(std::vector<int> vec);
int getVectorSumParallel(std::vector<int> vec, int vecCountSize);

#endif  // MODULES_TASK_1_VIZGALOV_A_VECTOR_SUM_VECTOR_SUM_H_
