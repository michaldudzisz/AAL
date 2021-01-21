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
#include <sstream>
#include "algo.h"

class InvalidCallException : public std::exception {
public:
    const char* what() const throw() {
        return "Invalid call";
    };
};

struct Config {
  std::string output_file_name_;
  std::string output_time_file_name_;
};

class Solver {
public:
  Solver();
  void handle_args(int argc, char** argv);
  void generate_all_solutions();
  std::pair<bool, double> solve_and_calc_time(
      const std::string&, const std::string&, int i);
  void args_info();

private:
  bool check_if_open(std::ofstream& f);
  bool check_if_open(std::ifstream& f);
  void generate_solutions(int i);

  std::unordered_map<int, Config> config_map_;
  std::string input_file_name_;
  bool if_count_time_;
  static const std::vector<bool(*)(const std::string&, const std::string&)>functions_;

};


#endif
