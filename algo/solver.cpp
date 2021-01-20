#include "solver.h"

using namespace std;

void Solver::test_params() {
  cout << "if_count_time_: " << if_count_time_ << endl;
  bool a = if_count_time_;
  cout << "input_file_name: " << input_file_name_ << endl;
  for_each(config_map_.begin(), config_map_.end(), [&](pair<int, Config> x) {
    cout << "x.output_file_name_ " << x.second.output_file_name_ << endl;
    if (a) {
      cout << "x.output_time_file_name_: " << x.second.output_time_file_name_ << endl; 
    }
  });
}

Solver::Solver() : if_count_time_(false) {
  
}

Config::Config () {

}

pair<bool, chrono::duration<double>> Solver::solve_and_calc_time(
    const string& a, const string& b, bool(*f)(const string&, const string&)) {
  bool ans;

  auto start = std::chrono::high_resolution_clock::now();
  ans = f(a, b); 
  auto finish = std::chrono::high_resolution_clock::now();

  chrono::duration<double> time = finish - start;
  chrono::duration<double> time_ms = chrono::duration_cast<chrono::milliseconds>(time);
  
  return make_pair(ans, time_ms);
}

void Solver::handle_args(int argc, char** argv) {
  for (int i = 1; i < argc; ++i) {
    cout << i << endl;
    switch (argv[i][1]) {
      case '0': {
        ++i;
        if (i == argc) throw InvalidCallException();
        
        Config config;
        config.output_file_name_ = string(argv[i]);

        if (if_count_time_) {
          ++i;
          if (i == argc) throw InvalidCallException();
          config.output_time_file_name_ = string(argv[i]);
        } 

        config_map_[0] = config;
        break;
      }
      case '1': {
        cout << "test1" << endl;
        ++i;
        if(i == argc) throw InvalidCallException();

        cout << "test1" << endl;

        Config config;
        config.output_file_name_ = string(argv[i]);

        cout << "test1" << endl;

        if (if_count_time_) {
          cout << "test32" << endl;
          ++i;
          if (i == argc) throw InvalidCallException();
          config.output_time_file_name_ = string(argv[i]);
        } 

        config_map_[1] = config;

        cout << "test1" << endl;

        }
        break;
      
      case 'i': ++i;
        if(i == argc) throw InvalidCallException();
        input_file_name_ = string(argv[i]);
        break;

      case 't': ++i;
        if(i != 2) throw InvalidCallException();
        if_count_time_ = true;
        break;
      
      default: break;
    }
  } 

  if (input_file_name_.empty()) 
    throw InvalidCallException();
}




