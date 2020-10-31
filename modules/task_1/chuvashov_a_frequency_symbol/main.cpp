// Copyright 2020 Chuvashov Artem
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <string>
#include "./frequency_symbol.h"

TEST(Parallel_Operations_MPI, test1) {
    int procrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procrank);
    std::string str;
    const int size = 7574;
    if (procrank == 0) {
        str = std::string(size, 'i');
        str[0] = 'w';
        str[54] = 'w';
        str[7573] = 'w';
    }
    int general_sum = amountFrequencySymbol(str, 'w', size);
    if (procrank == 0) {
        int summa = parallelFrecSym(str, 'w', size);
        ASSERT_EQ(summa, general_sum);
    }
}

TEST(Parallel_Operations_MPI, test2) {
    std::string general_string;
    const int size = 2;
    int procrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procrank);

    if (procrank == 0) {
        ASSERT_NO_THROW(general_string = getString(size));
    }
}

TEST(Parallel_Operations_MPI, test3) {
    int procrank;
    std::string general_string;
    const int size = 3445;
    MPI_Comm_rank(MPI_COMM_WORLD, &procrank);

    if (procrank == 0) {
        ASSERT_NO_THROW(general_string = getString(size));
    }
}

TEST(Parallel_Operations_MPI, test4) {
    int procrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procrank);
    std::string str;
    const int size = 10;
    if (procrank == 0) {
        str = getString(size);
    }
    int general_sum = amountFrequencySymbol(str, 'e', size);
    if (procrank == 0) {
        int summa = parallelFrecSym(str, 'e', size);
        ASSERT_EQ(summa, general_sum);
    }
}

TEST(Parallel_Operations_MPI, test5) {
    std::string general_string;
    const int size = -4;
    int procrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &procrank);

    if (procrank == 0) {
        ASSERT_ANY_THROW(general_string = getString(size));
    }
}

int main(int argc, char** argv) {
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
