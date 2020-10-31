// Copyright 2020 Anisimova Polina
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./wrong_vector.h"

TEST(Parallel_Operations_MPI, Test_Negative_Size) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  std::vector<int> vec;
  const int size_vector = -10;

  if (rank == 0) {
  ASSERT_ANY_THROW(getRandomVector(size_vector));
  }
}
TEST(Parallel_Operations_MPI, Test_Can_Generate_Random_Vector) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  const int count_size_vector = 100;
  if (rank == 0) {
  ASSERT_NO_THROW(getRandomVector(count_size_vector));
  }
}

TEST(Parallel_Operations_MPI, Test_Size_0) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  std::vector<int> vec;
  const int size_vector = 0;

  if (rank == 0) {
  ASSERT_NO_THROW(getRandomVector(size_vector));
  }
}

TEST(Parallel_Operations_MPI, Test_Made_Vector) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const int size_vector = 5;
  std::vector<int> vec(size_vector);

  if (rank == 0) {
  vec[0] = -1;
  vec[1] = 50;
  vec[2] = 15;
  vec[3] = 15;
  vec[4] = 2;
  }
  int sum = getParallelVector(vec, size_vector);

  if (rank == 0) {
  ASSERT_EQ(2, sum);
  }
}

TEST(Parallel_Operations_MPI, Test_Vector_0) {
  int Size = 5;
  std::vector<int> vec = { 0, 0, 0, 0, 0 };
  int sum = 0;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int vec_sum = getParallelVector(vec, Size);

  if (rank == 0) {
  ASSERT_EQ(vec_sum, sum);
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
