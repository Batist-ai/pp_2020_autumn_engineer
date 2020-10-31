// Copyright 2020 Sandalov Konstantin
#ifndef MODULES_TASK_1_SANDALOV_K_SYMBOL_FREQUENCY_SYMBOL_FREQUENCY_H_
#define MODULES_TASK_1_SANDALOV_K_SYMBOL_FREQUENCY_SYMBOL_FREQUENCY_H_

#include <string>

std::string getRandomString(int string_size);
int countFrequencyPar(const std::string& global_string, char symbol, int string_size);
int countFrequencySec(const std::string& current_string, char symbol, int string_size);

#endif  // MODULES_TASK_1_SANDALOV_K_SYMBOL_FREQUENCY_SYMBOL_FREQUENCY_H_
