#include <iostream>
#include "algo.h"
#include "test.h"
#include <vector>
#include "solver.h"

using namespace std;

int main(int argc, char** argv) {

  Solver solver;
  solver.handle_args(argc, argv);
  cout << "nowy teest" << endl;
  solver.test_params();
//  solver.generate_solutions();
  
  return 0;
}

