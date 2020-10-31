// Copyright 2020 Schelyanskova Anastasiya
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/schelyanskova_a_matrix_min_value_rows/matrix_min_value_rows.h"

TEST(Schelyanskova_task_1, Seq_test_1) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> res(2);

    res = getSequentialOperations(vec, 2, 5);
    std::vector<int> expected = { 1, 6 };
    if (rank == 0) {
        ASSERT_EQ(res, expected);
    }
}

TEST(Schelyanskova_task_1, Paral_test_2) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    if (rank == 0) {
        vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    }
    std::vector<int> expected(2);
    std::vector<int> res(2);

    expected = {1, 6};
    res = getParallelOperations(vec, 2, 5);

    if (rank == 0) {
        ASSERT_EQ(expected, res);
    }
}

TEST(Schelyanskova_task_1, Paral_test_3) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec(100);
    for (int i = 0; i < 100; i++) {
        vec[i] = i;
    }
    std::vector<int> expected(10);
    std::vector<int> res(10);

    expected = getSequentialOperations(vec, 10, 10);
    res = getParallelOperations(vec, 10, 10);

    if (rank == 0) {
        ASSERT_EQ(expected, res);
    }
}

TEST(Schelyanskova_task_1, Paral_test_4) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec(1500);
    if (rank == 0) {
        vec = getRandomMatrix(30, 50);
    }
    std::vector<int> expected(30);
    std::vector<int> res(30);

    expected = getSequentialOperations(vec, 30, 50);
    res = getParallelOperations(vec, 30, 50);

    if (rank == 0) {
        ASSERT_EQ(expected, res);
    }
}

TEST(Schelyanskova_task_1, Paral_test_5) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec(15);
    for (int i = 0; i < 15; i++) {
        vec[i] = i;
    }
    std::vector<int> expected(15);
    std::vector<int> res(15);

    expected = getSequentialOperations(vec, 15, 1);
    res = getParallelOperations(vec, 15, 1);

    if (rank == 0) {
        ASSERT_EQ(expected, res);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

#ifdef _DEBUG

    int rank, temp;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {
        std::cout << "Please input number: ";
        std::cin >> temp;
    }

    MPI_Barrier(MPI_COMM_WORLD);

#endif


    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
