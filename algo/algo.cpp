#include "algo.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// dynamic programming solution O(n*m)
bool solve_dynamic_programming_opt(const string& a, const string& b) {
  int n = a.length(); int m = b.length();

  vector<vector<bool>> arr (n+1, vector<bool> (m+1, false));
  arr[0][0] = true;

  bool b_contains_lower = false;
  
  for_each(b.begin(), b.end(), [&](const char& c) {
      if (islower(c)) b_contains_lower = true;
    });

  for (int i = 0; i < a.length(); ++i) 
  {
    for (int j = 0; j < b.length() + 1; ++j) 
    {
      if (arr[i][j]) {

        if (j < b.length()) {

          if (a[i] == b[j]) {
            arr[i + 1][j + 1] = true;
          }

          else if (toupper(a[i]) == b[j] && !b_contains_lower)  {
            arr[i + 1][j + 1] = true;
          }

        }

        if (!isupper(a[i]) && !b_contains_lower) 
          arr[i + 1][j] = true; 
      }
    }
  }
  return arr[n][m];
}


string del_low_case(string& s);
bool helper (const string& b, string s, int i);

// brute force solution generate all permutations
bool bf(const string& a, const string& b) {
    if (a == b) return true;
    string a_tmp = a;
    return helper(b, a_tmp, 0);
}

string del_low_case (string& s) {
    string ans = "";
    for (const char& ch : s) if(isupper(ch)) ans += ch;
    return ans;
}

bool helper(const string& b, string s, int i) {
    if (i == s.length()) return b == del_low_case(s);
    bool res = helper(b, s, i + 1);
    if (islower(s[i])) { 
        s[i] = toupper(s[i]);   
        res = res || helper(b, s, i + 1);
    }
    return res;
}


