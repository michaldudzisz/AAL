#ifndef SOLVER_H_
#define SOLVER_H_

#include <fstream>
#include <exception>
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include "algo.h"

class InvalidCallException : public std::exception {
public:
    const char* what() const throw() {
        return "Invalid call";
    };
};

struct Config {
  Config();

  std::string output_file_name_;
  std::string output_time_file_name_;
};

class Solver {
public:
  Solver();
  void handle_args(int argc, char** argv);
  void generate_solutions();
  std::pair<bool, std::chrono::duration<double>> solve_and_calc_time(
      const std::string&, const std::string&, bool(*)(const std::string&, const std::string&));
  void args_info();

private:
  std::unordered_map<int, Config> config_map_;
  std::string input_file_name_;
  bool if_count_time_;
  static const std::vector<bool(*)(const std::string&, const std::string&)>functions_;
};


#endif
