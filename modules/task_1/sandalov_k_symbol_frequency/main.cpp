// Copyright 2020 Sandalov Konstantin
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../../../modules/task_1/sandalov_k_symbol_frequency/symbol_frequency.h"

TEST(Parallel_Operations_MPI, create_random_string) {
    std::string global_string;
    const int string_size = 1000;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    if (proc_rank == 0) {
        ASSERT_NO_THROW(global_string = getRandomString(string_size));
    }
}

TEST(Parallel_Operations_MPI, create_random_string_with_small_size) {
    std::string global_string;
    const int string_size = 2;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    if (proc_rank == 0) {
        ASSERT_NO_THROW(global_string = getRandomString(string_size));
    }
}

TEST(Parallel_Operations_MPI, create_string_with_wrong_size) {
    std::string global_string;
    const int string_size = -13;
    int proc_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    if (proc_rank == 0) {
        ASSERT_ANY_THROW(global_string = getRandomString(string_size));
    }
}

TEST(Parallel_Operations_MPI, test_comparison) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string global_string;
    const int string_size = 100;
    if (rank == 0) {
        global_string = getRandomString(string_size);
    }
    int global_sum = countFrequencyPar(global_string, 's', string_size);
    if (rank == 0) {
        int reference_sum = countFrequencySec(global_string, 's', string_size);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Parallel_Operations_MPI, test_comparison_with_big_string_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string global_string;
    const int string_size = 1000000;
    if (rank == 0) {
        global_string = getRandomString(string_size);
    }
    int global_sum = countFrequencyPar(global_string, 'k', string_size);
    if (rank == 0) {
        int reference_sum = countFrequencySec(global_string, 'k', string_size);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Parallel_Operations_MPI, test_comparison_with_small_string_size) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string global_string;
    const int string_size = 2;
    if (rank == 0) {
        global_string = getRandomString(string_size);
    }
    int global_sum = countFrequencyPar(global_string, 'y', string_size);
    if (rank == 0) {
        int reference_sum = countFrequencySec(global_string, 'y', string_size);
        ASSERT_EQ(reference_sum, global_sum);
    }
}

TEST(Parallel_Operations_MPI, test_comparison_with_my_string) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::string global_string;
    const int string_size = 1111;
    if (rank == 0) {
        global_string = std::string(string_size, 'i');
        global_string[0] = 'T';
        global_string[1110] = 'T';
        global_string[521] = 'T';
    }
    int global_sum = countFrequencyPar(global_string, 'T', string_size);
    if (rank == 0) {
        int reference_sum = countFrequencySec(global_string, 'T', string_size);
        ASSERT_EQ(reference_sum, global_sum);
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
