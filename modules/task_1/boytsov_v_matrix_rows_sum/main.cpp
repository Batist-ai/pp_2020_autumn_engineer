// Copyright 2020 Boytsov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_rows_sum.h"

TEST(Parallel_Operation_MPI, Sequential_operations_run) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int> > mat;
    std::vector<int> resultVector;
    std::vector<int> sequentialResult;
    if (rank == 0) {
    mat = std::vector<std::vector<int> >({{1, 1, 1, 1},
                                          {2, 2, 2, 2},
                                          {1, 2, 3, 4}});
        resultVector = std::vector<int>({4, 8, 10});
        sequentialResult = getSequentialSumOfRows(matrixToVector(mat), 3, 4);

        EXPECT_EQ(sequentialResult, resultVector);
    }
}

TEST(Parallel_Operation_MPI, Parallel_operations_run) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int> > mat;
    std::vector<int> resultVector;
    std::vector<int> parallelResult;
    if (rank == 0) {
        mat = std::vector<std::vector<int> >({{1, 1, 1, 1},
                                             {2, 2, 2, 2},
                                             {1, 2, 3, 4}});
        resultVector = std::vector<int>({4, 8, 10});
    }
    parallelResult = getParallelSumOfRows(mat, 3, 4);
    if (rank == 0) {
        EXPECT_EQ(parallelResult, resultVector);
    }
}

TEST(Parallel_Operation_MPI, Can_create_matrix) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int M = 100;
    const int N = 500;
    if (rank == 0) {
        ASSERT_NO_THROW(createRandomMatrix(M, N));
    }
}

TEST(Parallel_Operation_MPI, Negative_matrix_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        EXPECT_ANY_THROW(createRandomMatrix(-6, -3));
    }
}

TEST(Parallel_Operation_MPI, ParallelResults_vs_SequentialResults) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<std::vector<int> > mat;
    const int M = 1000;
    const int N = 1000;
    std::vector<int> sequentialResult;
    std::vector<int> parallelResult;
    if (rank == 0) {
        mat = createRandomMatrix(M, N);
    }
    parallelResult = getParallelSumOfRows(mat, M, N);
    if (rank == 0) {
        sequentialResult = getSequentialSumOfRows(matrixToVector(mat), M, N);
        EXPECT_EQ(parallelResult, sequentialResult);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
