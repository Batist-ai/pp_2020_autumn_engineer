// Copyright 2020 Vizgalov Anton
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./vector_sum.h"

void createTestForSize(int size);

TEST(Vector_Sum_MPI, Test_Empty) {
    createTestForSize(0);
}

TEST(Vector_Sum_MPI, Test_Sum_10) {
    createTestForSize(10);
}

TEST(Vector_Sum_MPI, Test_Sum_100) {
    createTestForSize(100);
}

TEST(Vector_Sum_MPI, Test_Sum_1000) {
    createTestForSize(1000);
}

TEST(Vector_Sum_MPI, Test_Sum_10000) {
    createTestForSize(10000);
}

TEST(Vector_Sum_MPI, Test_Sum_333) {
    createTestForSize(333);
}

void createTestForSize(int size) {
    int procRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    std::vector<int> testVec;
    const int testSize = size;

    if (procRank == 0) {
        testVec = getRandomVector(testSize);
    }

    int resultSum = getVectorSumParallel(testVec, testSize);

    if (procRank == 0) {
        int gtSum = getVectorSumSequential(testVec);
        ASSERT_EQ(gtSum, resultSum);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());
    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);

    return RUN_ALL_TESTS();
}
