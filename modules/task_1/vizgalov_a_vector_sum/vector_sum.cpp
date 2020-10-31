// Copyright 2020 Vizgalov Anton
#include <mpi.h>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

std::vector<int> getRandomVector(int size) {
    std::mt19937 randGenerator;
    randGenerator.seed(static_cast<unsigned>(time(NULL)));

    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = randGenerator() % 100;
    }

    return vec;
}

int getVectorSumSequential(std::vector<int> vec) {
    int vecSum = 0;

    for (size_t i = 0; i < vec.size(); ++i) {
        vecSum += vec[i];
    }

    return vecSum;
}

int getVectorSumParallel(std::vector<int> vec, int vecCountSize) {
    int commSize, procRank;
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    const int numPerProc = vecCountSize / commSize;
    const int leftover = vecCountSize % commSize;

    if (procRank == 0) {
        for (int procNum = 1; procNum < commSize; ++procNum) {
            MPI_Send(&vec[0] + procNum * numPerProc + std::min(procNum, leftover),
                     numPerProc + (procNum < leftover ? 1 : 0),
                     MPI_INT, procNum, 0, MPI_COMM_WORLD);
        }
    }

    std::vector<int> subVector(numPerProc + 1);
    if (procRank == 0) {
        subVector = std::vector<int>(vec.begin(), vec.begin() + numPerProc + (leftover > 0 ? 1 : 0));
    } else {
        MPI_Status status;
        MPI_Recv(&subVector[0], numPerProc + (procRank < leftover ? 1 : 0), MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    int sum = 0;
    int subSum = getVectorSumSequential(subVector);
    MPI_Reduce(&subSum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return sum;
}
