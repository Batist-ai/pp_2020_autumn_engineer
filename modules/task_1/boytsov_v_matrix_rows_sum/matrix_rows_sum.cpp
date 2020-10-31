// Copyright 2020 Boytsov Vladislav
#include "../../../modules/task_1/boytsov_v_matrix_rows_sum/matrix_rows_sum.h"
#include <mpi.h>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

std::vector<std::vector<int> > createRandomMatrix(const int M, const int N) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<std::vector<int> > mat(M);
    for (int i = 0; i < M; ++i) {
        mat[i] = std::vector<int>(N);
        for (int j = 0; j < N; ++j) {
            mat[i][j] = gen() % 100;
        }
    }
    return mat;
}

std::vector<int> getSequentialSumOfRows(const std::vector<int> vec, const int M, const int N) {
    std::vector<int> result(M);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            result[i] += vec[i * N + j];
    return result;
}

std::vector<int> matrixToVector(std::vector<std::vector<int> > mat) {
    const int M = mat.size();
    const int N = mat[0].size();
    std::vector<int> result;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            result.push_back(mat[i][j]);
    return result;
}

std::vector<int> getParallelSumOfRows(const std::vector<std::vector<int> > mat, const int M, const int N) {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int delta = M / size;
    int rest = M % size;
    std::vector<int> localVector;

    if (rank == 0) {
        localVector = matrixToVector(mat);
        for (int i = 1; i < size; ++i) {
            MPI_Send(&localVector[0] + i * N * delta, N * delta, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    std::vector<int> localVectorFirst(delta * N);
    std::vector<int> localVectorLast(rest * N);
    if (rank == 0) {
        localVectorFirst = std::vector<int>(localVector.begin(), localVector.begin() + delta * N);
        if (rest != 0)
            localVectorLast = std::vector<int>(localVector.end() - rest * N, localVector.end());
    } else {
        MPI_Status status;
        MPI_Recv(&localVectorFirst[0], N * delta, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    std::vector<int> localVectorFirstResult(delta);
    std::vector<int> localVectorLastResult(rest);
    localVectorFirstResult = getSequentialSumOfRows(localVectorFirst, delta, N);
    if (rest != 0 && rank == 0)
        localVectorLastResult = getSequentialSumOfRows(localVectorLast, rest, N);
    std::vector<int> globalVectorResult(M);
    MPI_Gather(&localVectorFirstResult[0], delta, MPI_INT,
               &globalVectorResult[0], delta, MPI_INT, 0, MPI_COMM_WORLD);
    if (rest != 0 && rank == 0) {
        for (int i = 0; i < rest; ++i)
            globalVectorResult[M - rest + i] = localVectorLastResult[i];
    }
    return globalVectorResult;
}

