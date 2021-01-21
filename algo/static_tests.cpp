#include <iostream>
#include "algo.h"
#include "test.h"

using namespace std;

int main(int argc, char** argv) {
  run_tests(&bf);
//  run_tests(&solve_dynamic_programming);
  run_tests(&solve_dynamic_programming_opt);
}
