// Copyright 2020 el fahli meryem
#include <mpi.h>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/elfahli_sents_in_line/sents_mpi.h"

std::vector<char> getRL(int s) {
    std::vector<char> l(s);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    int symbol;
    for (int i = 0; i < s; i++) {
        symbol = gen() % 255;
        l[i] = static_cast<char>(symbol);
    }
    return l;
}

int getSeqSumSents(std::vector<char> l) {
    const int  size = l.size();
    int a = 0;
    for (int i = 0; i < size; i++) {
        if (l[i] == '!' || l[i] == '?' || l[i] == '.') a++;
    }
    return a;
}

int getParallelSumSents(std::vector<char> g_line, int s_line) {
    int s, r;
    MPI_Comm_size(MPI_COMM_WORLD, &s);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    const int d = s_line / s;
    const int tmp = d * s;
    const int k = s_line - tmp;
    if (r == 0) {
        for (int pr = 1; pr < s; pr++) {
            MPI_Send(&g_line[0] + k + pr * d, d, MPI_CHAR, pr, 0, MPI_COMM_WORLD);
        }
    }
    int vls = 0;
    if (r == 0) {
        vls = k + d;
    } else {
        vls = d;
    }
    std::vector<char> l_line(vls);
    if (r == 0) {
        l_line = std::vector<char>(g_line.begin(), g_line.begin() + k + d);
    } else {
        MPI_Status status;
        MPI_Recv(&l_line[0], d, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    }
    int global_sum_sentences = 0;
    int local_sum_sentences = getSeqSumSents(l_line);
    MPI_Reduce(&local_sum_sentences, &global_sum_sentences, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum_sentences;
}
