// Copyright 2020 el fahli meryem
#ifndef MODULES_TASK_1_ELFAHLI_SENTS_IN_LINE_SENTS_MPI_H_
#define MODULES_TASK_1_ELFAHLI_SENTS_IN_LINE_SENTS_MPI_H_

#include <vector>

std::vector<char> getRL(int  s);
int getParallelSumSents(std::vector<char> g_line, int s_line);
int getSeqSumSents(std::vector<char> l);


#endif  // MODULES_TASK_1_ELFAHLI_SENTS_IN_LINE_SENTS_MPI_H_
