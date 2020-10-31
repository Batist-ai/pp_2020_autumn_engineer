// Copyright 2020 Anisimova Polina
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_1/anisimova_p_wrong_vector/wrong_vector.h"


std::vector<int> getRandomVector(int sz) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec(sz);
    for (int  i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

  int getSequentialPart(std::vector<int> vec, int sz) {
  if (sz == 0) return 0;

  int sum = 0;
  for (int i = 0; i < sz - 1; i++) {
     if (vec[i] > vec[i + 1])
             sum++;
  }
  return sum;
}

int getParallelVector(std::vector<int> global_vec, int size_vector) {
  if (size_vector == 0)
    return 0;

  int size, rank, GlobalSum = 0, LocalSum = 0;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int delta = size_vector/size;
  int rest =  size_vector%size;

  if (rank == 0) {
    for (int i = 1; i < size; i++) { MPI_Send(&global_vec[0] + i * delta + rest - 1,
  delta, MPI_INT, i, 0, MPI_COMM_WORLD);
  }
  }
  MPI_Status status;

if (rank == 0) {
std::vector<int> local_vec(delta + rest);
  local_vec = std::vector<int>(global_vec.begin(), global_vec.begin() + delta + rest);
  LocalSum = getSequentialPart(local_vec, static_cast<int>(local_vec.size()));
  } else {
    std::vector<int> local_vec(delta + 1);
    MPI_Recv(&local_vec[0], delta + 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    LocalSum = getSequentialPart(local_vec, static_cast<int>(local_vec.size()));
  }

  MPI_Reduce(&LocalSum, &GlobalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  return GlobalSum;
  }
