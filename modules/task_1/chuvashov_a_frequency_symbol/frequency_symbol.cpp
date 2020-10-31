// Copyright 2020 Chuvashov Artem
#include <mpi.h>
#include <ctime>
#include <random>
#include <string>
#include "../../../modules/task_1/chuvashov_a_frequency_symbol/frequency_symbol.h"


std::string getString(int size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::string str_res;
    str_res.resize(size);
    for (auto& smb : str_res) {
        smb = static_cast<char>(gen() % 100);
    }
    return str_res;
}

int parallelFrecSym(const std::string& general_str, char character, int size) {
    int frequency = 0;
    for (int j = 0; j < size; j++) {
        if (general_str[j] == character) {
            frequency++;
        }
    }
    return frequency;
}

int amountFrequencySymbol(const std::string& flow_str, char character, int Size) {
    int procsize, procrank;
    MPI_Comm_size(MPI_COMM_WORLD, &procsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &procrank);

    if (Size < procsize) {
        if (procrank == 0)
            return parallelFrecSym(flow_str, character, Size);
        else
            return 0;
    }
    const int delta_ = Size / procsize;
    int Sizestr;
    if (procrank == procsize - 1)
        Sizestr = Size - (procsize - 1) * delta_;
    else
        Sizestr = delta_;

    if (procrank == 0 && procsize > 1) {
        for (int process = 1; process < procsize - 1; ++process) {
            MPI_Send(&flow_str[process * delta_], delta_,
                MPI_CHAR, process, 0, MPI_COMM_WORLD);
        }
        MPI_Send(&flow_str[(procsize - 1) * delta_], Size - (procsize - 1) * delta_,
            MPI_CHAR, procsize - 1, 0, MPI_COMM_WORLD);
    }
    int frequency_summa = 0;
    int local_summa = 0;
    std::string local_buf;
    local_buf.resize(delta_);
    if (procrank == 0) {
        local_summa = parallelFrecSym(flow_str, character, delta_);
    } else {
        MPI_Status status;
        MPI_Recv(&local_buf[0], Sizestr, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        local_summa = parallelFrecSym(local_buf, character, Sizestr);
    }

    MPI_Reduce(&local_summa, &frequency_summa, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    return frequency_summa;
}
