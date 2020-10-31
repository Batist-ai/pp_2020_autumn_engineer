// Copyright 2020 Schelyanskova Anastasiya
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <climits>
#include <algorithm>
#include "../../../modules/test_tasks/test_mpi/ops_mpi.h"
#include "../../../modules/task_1/schelyanskova_a_matrix_min_value_rows/matrix_min_value_rows.h"

std::vector<int> getRandomMatrix(int rows, int colls) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<> dist(0, 100);
    std::vector<int> Matrix;
    if (rows > 0 && colls > 0) {
        Matrix.resize(rows * colls);
        for (int i = 0; i < rows * colls; ++i) {
            Matrix[i] = dist(gen) % 100;
        }
    }
    return Matrix;
}

std::vector<int> getSequentialOperations(std::vector<int> Matrix, int rows, int colls) {
    std::vector<int> MinRowsValues;
    if (Matrix.size() > 0 && rows > 0 && colls > 0) {
        MinRowsValues.resize(rows);
        int MinValue = INT_MAX;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < colls; j++) {
                if (MinValue > Matrix[i * colls + j]) MinValue = Matrix[i * colls + j];
            }
            MinRowsValues[i] = MinValue;
            MinValue = INT_MAX;
        }
    }
    return MinRowsValues;
}

std::vector<int> getParallelOperations(std::vector<int> Matrix, int rows, int colls) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int delta = rows / size;
    std::vector<int> rez(rows);
    std::vector<int> local_rez(delta);
    std::vector<int> local_matrix(delta * colls);

    MPI_Scatter(&Matrix[0], delta * colls, MPI_INT, &local_matrix[0], delta * colls, MPI_INT, 0, MPI_COMM_WORLD);

    local_rez = getSequentialOperations(local_matrix, delta, colls);

    MPI_Gather(&local_rez[0], delta, MPI_INT, &rez[0], delta, MPI_INT, 0, MPI_COMM_WORLD);
    if ((rank == 0) && (rows % size != 0)) {
        for (int i = delta * size; i < rows; i++) {
            rez[i] = Matrix[i * colls];
            for (int j = 1; j < colls; j++)
                if (Matrix[i * colls + j] < rez[i])
                    rez[i] = Matrix[i * colls + j];
        }
    }
    return rez;
}
