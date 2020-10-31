// Copyright 2020 el fahli meryem
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./sents_mpi.h"

TEST(Parallel_MPI, Test_Sentences_Length_0) {
    int r;
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    std::vector<char> g_line;
    const int s_line = 0;
    if (r == 0) {
        g_line = getRL(s_line);
    }

    int gss = getParallelSumSents(g_line, s_line);
    if (r == 0) {
        int rss = getSeqSumSents(g_line);
        ASSERT_EQ(rss, gss);
    }
}

TEST(Parallel_MPI, Test_Sentences_Length_1) {
    int r;
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    std::vector<char> g_line;
    const int s_line = 1;
    if (r == 0) {
        g_line = getRL(s_line);
    }

    int gss = getParallelSumSents(g_line, s_line);
    if (r == 0) {
        int rss = getSeqSumSents(g_line);
        ASSERT_EQ(rss, gss);
    }
}

TEST(Parallel_MPI, Test_Sentences_Length_10) {
    int r;
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    std::vector<char> g_line;
    const int s_line = 10;
    if (r == 0) {
        g_line = getRL(s_line);
    }

    int gss = getParallelSumSents(g_line, s_line);
    if (r == 0) {
        int rss = getSeqSumSents(g_line);
        ASSERT_EQ(rss, gss);
    }
}

TEST(Parallel_MPI, Test_Sentences_Length_50) {
    int r;
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    std::vector<char> g_line;
    const int s_line = 50;
    if (r == 0) {
        g_line = getRL(s_line);
    }

    int gss = getParallelSumSents(g_line, s_line);
    if (r == 0) {
        int rss = getSeqSumSents(g_line);
        ASSERT_EQ(rss, gss);
    }
}

TEST(Parallel_MPI, Test_Sentences_Length_100) {
    int r;
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    std::vector<char> g_line;
    const int s_line = 100;
    if (r == 0) {
        g_line = getRL(s_line);
    }

    int gss = getParallelSumSents(g_line, s_line);
    if (r == 0) {
        int rss = getSeqSumSents(g_line);
        ASSERT_EQ(rss, gss);
    }
}


TEST(Parallel_MPI, Test_Sentences_Length_1000) {
    int r;
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    std::vector<char> g_line;
    const int s_line = 1000;
    if (r == 0) {
        g_line = getRL(s_line);
    }

    int gss = getParallelSumSents(g_line, s_line);
    if (r == 0) {
        int rss = getSeqSumSents(g_line);
        ASSERT_EQ(rss, gss);
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
