#include "solver.h"

using namespace std;

const vector<bool(*)(const string&, const string&)> Solver::functions_ = {
  &bf, 
  &solve_dynamic_programming, 
  &solve_dynamic_programming_opt
};

Solver::Solver() : if_count_time_(false) {
  
}

bool Solver::check_if_open(ifstream& f) {
    if (!f.is_open()) {
      cout << "error opening the file" << endl;
      return 0;
    }
    return 1;
}

bool Solver::check_if_open(ofstream& f) {
    if (!f.is_open()) {
      cout << "error opening the file" << endl;
      return 0;
    }
    return 1;
}

void Solver::generate_solutions(int i) {
  ifstream input_file(input_file_name_);
  ofstream output_file(config_map_[i].output_file_name_);
  ofstream output_time_file;

  if (if_count_time_) {
    output_time_file.open(config_map_[i].output_time_file_name_);
    if (!check_if_open(output_time_file)) return;
  }
  if (!check_if_open(input_file) || !check_if_open(output_file)) return;

  string line;
  while(getline (input_file,line)) {
    size_t pos = line.find(' ');
    const string a = line.substr(0, pos); 
    const string b = line.substr(pos + 1);
    if (if_count_time_) {
      auto solution = solve_and_calc_time(a,b,i);
      output_file << a << " " << b << " " << solution.first << "\n";
      output_time_file << a.length() << " " << b.length() << " " << solution.second << "\n";
    } else {
      output_file << a << " " << b << " " << functions_[i](a,b) << "\n"; 
    }
  }
  output_file.close();
  input_file.close();
  if (if_count_time_) output_time_file.close();
}

void Solver::generate_all_solutions() {
  
  for (auto elem : config_map_) {
    generate_solutions(elem.first);  
  }
}

void Solver::args_info() {

  if (if_count_time_) {
    cout << "count time: yes" << endl;
  } else {
    cout << "count time: no" << endl;
  }

  bool a = if_count_time_;
  cout << "input_file_name: " << input_file_name_ << endl;
  for_each(config_map_.begin(), config_map_.end(), [&](pair<int, Config> x) {
    cout << "algorithm nr: " << x.first << endl;
    cout << "x.output_file_name_ " << x.second.output_file_name_ << endl;
    if (a) {
      cout << "x.output_time_file_name_: " << x.second.output_time_file_name_ << endl; 
    }
  });
}

pair<bool, double> Solver::solve_and_calc_time(
    const string& a, const string& b, int i) {
  bool ans;

  auto start = std::chrono::high_resolution_clock::now();
  ans = functions_[i](a, b); 
  auto finish = std::chrono::high_resolution_clock::now();

  chrono::duration<double> time = finish - start;
  chrono::duration<double> time_ms = chrono::duration_cast<chrono::milliseconds>(time);
  
  return make_pair(ans, time_ms.count());
}

void Solver::handle_args(int argc, char** argv) {
  for (int i = 1; i < argc; ++i) {
    if ((argv[i][0] == '-' || argv[i][0] == '/') && std::string(argv[i]).length() == 2) {
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
          ++i;
          if(i == argc) throw InvalidCallException();  
          Config config;
          config.output_file_name_ = string(argv[i]);
          if (if_count_time_) {
            ++i;
            if (i == argc) throw InvalidCallException();
            config.output_time_file_name_ = string(argv[i]);
          }
          config_map_[1] = config;
          }
          break;

        case '2': {
          ++i;
          if(i == argc) throw InvalidCallException();  
          Config config;
          config.output_file_name_ = string(argv[i]);
          if (if_count_time_) {
            ++i;
            if (i == argc) throw InvalidCallException();
            config.output_time_file_name_ = string(argv[i]);
          }
          config_map_[2] = config;
          }
          break;
        
        case 'i': ++i;
          if(i == argc) throw InvalidCallException();
          input_file_name_ = string(argv[i]);
          break;

        case 't': 
          if(i != 1) throw InvalidCallException();
          if_count_time_ = true;
          break;
        
        default: break;
      }
    } else {
      throw InvalidCallException();
    }
  }
  if (input_file_name_.empty()) throw InvalidCallException();
}
