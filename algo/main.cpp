#include <iostream>
#include "algo.h"
#include "test.h"
#include <vector>
#include "solver.h"
#include <exception>

using namespace std;

int main(int argc, char** argv) {

  Solver solver;

  try {
    solver.handle_args(argc, argv);
  } catch(exception& e) {
    cout << e.what() << endl;
    return 0;
  }

  solver.args_info();
  solver.generate_all_solutions();
  
  return 0;
}

