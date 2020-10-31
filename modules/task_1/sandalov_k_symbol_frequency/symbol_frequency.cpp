// Copyright 2020 Sandalov Konstantin
#include <mpi.h>
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "../../../modules/task_1/sandalov_k_symbol_frequency/symbol_frequency.h"


std::string getRandomString(int string_size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::string ret_string;
    ret_string.resize(string_size);
    for (auto& symbol : ret_string) {
        symbol = static_cast<char>(gen() % 100);
    }
    return ret_string;
}

int countFrequencySec(const std::string& current_string, char symbol, int string_size) {
    int frequency_count = 0;
    for (int i = 0; i < string_size; ++i) {
        if (current_string[i] == symbol) ++frequency_count;
    }
    return frequency_count;
}

int countFrequencyPar(const std::string& global_string, char symbol, int string_size) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (string_size < size) {
        if (rank == 0)
            return countFrequencySec(global_string, symbol, string_size);
        else
            return 0;
    }
    const int delta = string_size / size;
    int real_size;
    if (rank == size - 1)
        real_size = string_size - (size - 1) * delta;
    else
        real_size = delta;

    if (rank == 0 && size > 1) {
        for (int proc_num = 1; proc_num < size - 1; ++proc_num) {
            MPI_Send(&global_string[proc_num * delta], delta,
                        MPI_CHAR, proc_num, 0, MPI_COMM_WORLD);
        }
        MPI_Send(&global_string[(size - 1) * delta], string_size - (size - 1) * delta,
                        MPI_CHAR, size - 1, 0, MPI_COMM_WORLD);
    }
    int global_sum = 0;
    int local_sum = 0;
    std::string local_string;
    local_string.resize(delta);
    if (rank == 0) {
        local_sum = countFrequencySec(global_string, symbol, delta);
    } else {
        MPI_Status status;
        MPI_Recv(&local_string[0], real_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        local_sum = countFrequencySec(local_string, symbol, real_size);
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum;
}
