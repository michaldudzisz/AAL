#include <iostream>
#include "algo.h"
#include "test.h"

using namespace std;

int main(int argc, char** argv) {
  run_tests(&bf);
  run_tests(&solve_dp);
}
