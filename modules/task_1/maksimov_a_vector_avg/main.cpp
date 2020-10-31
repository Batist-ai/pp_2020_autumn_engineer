// Copyright 2020 Maksimov Andrey
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>

#include <vector>

#include "../../modules/task_1/maksimov_a_vector_avg/vec_avg.h"

TEST(Parallel_Operations_MPI, Can_Generate_Vector) {
    const int vecSize = 10;

    std::vector<int> vec = getRandomVector(vecSize);
    ASSERT_EQ(static_cast<int>(vec.size()), vecSize);
}

TEST(Parallel_Operations_MPI, Test_Negative_VecSize) {
    const int vecSize = -10;

    ASSERT_ANY_THROW(getRandomVector(vecSize));
}

TEST(Parallel_Operations_MPI, Test_Size_1) {
    const int vecSize = 1;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    if (rank == 0) {
        vec = getRandomVector(vecSize);
    }
    int avg = getVectorAvg(vec, vecSize);
    if (rank == 0) {
        int avgNotParall = getVectorAvgNotParall(vec, vecSize);
        ASSERT_EQ(avgNotParall, avg);
    }
}

TEST(Parallel_Operations_MPI, Test_Size_Tiny) {
    const int vecSize = 10;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    if (rank == 0) {
        vec = getRandomVector(vecSize);
    }
    int avg = getVectorAvg(vec, vecSize);
    if (rank == 0) {
        int avgNotParall = getVectorAvgNotParall(vec, vecSize);
        ASSERT_EQ(avgNotParall, avg);
    }
}
TEST(Parallel_Operations_MPI, Test_Size_Medium) {
    const int vecSize = 100;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    if (rank == 0) {
        vec = getRandomVector(vecSize);
    }
    int avg = getVectorAvg(vec, vecSize);
    if (rank == 0) {
        int avgNotParall = getVectorAvgNotParall(vec, vecSize);
        ASSERT_EQ(avgNotParall, avg);
    }
}

TEST(Parallel_Operations_MPI, Test_Size_Huge) {
    const int vecSize = 1000;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vec;
    if (rank == 0) {
        vec = getRandomVector(vecSize);
    }
    int avg = getVectorAvg(vec, vecSize);
    if (rank == 0) {
        int avgNotParall = getVectorAvgNotParall(vec, vecSize);
        ASSERT_EQ(avgNotParall, avg);
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);

    return RUN_ALL_TESTS();
}
