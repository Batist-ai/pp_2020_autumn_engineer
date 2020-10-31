// Copyright 2020 Anisimova Polina
#ifndef MODULES_TASK_1_ANISIMOVA_P_WRONG_VECTOR_WRONG_VECTOR_H_
#define MODULES_TASK_1_ANISIMOVA_P_WRONG_VECTOR_WRONG_VECTOR_H_

#include <vector>
#include <string>

std::vector<int> getRandomVector(int  sz);
int getParallelVector(std::vector<int> global_vec, int count_size_vector);
int getSequentialPart(std::vector<int> vec);

#endif  // MODULES_TASK_1_ANISIMOVA_P_WRONG_VECTOR_WRONG_VECTOR_H_
