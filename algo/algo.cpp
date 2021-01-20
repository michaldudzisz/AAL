#include "algo.h"
#include <iostream>
#include <vector>
using namespace std;

bool solver_a (string a, string b) {
  bool b_contains_lower = false; 
  for (int i = 0; i < b.length(); ++i) 
    if (islower(b[i])) {b_contains_lower = true; break;}

  int tmp = 0; 

  for (int i = 0; i < b.length(); ++i) {

    int pos = a.substr(tmp).find(b[i]);   

    if (pos == string::npos && b_contains_lower) return false; 

    if (pos == string::npos && isupper(b[i])) 
      pos = a.substr(tmp).find(tolower(b[i]));

    if (pos == string::npos) return false;

    pos += tmp;

    for (int j = tmp; j < pos; ++j) 
      if (b_contains_lower || isupper(a[j])) return false;

    tmp = pos + 1;
  }

  for (int i = tmp; i < a.length(); ++i) 
    if (b_contains_lower || isupper(a[i])) return false;

  return true;
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

bool bf(string a, string b) {
    if (a == b) return true;
    return helper(b, a, 0);
}

void print_vec (vector<vector<bool>> V) {
  for (int i = 0; i < V.size(); ++i) {
    for (int j = 0; j < V[i].size(); ++j) {
      cout << V[i][j] << " ";
    }
    cout << endl;
  }
}
  

bool solve_dp(string a, string b) {
  int n = a.length();
  int m = b.length();

  vector<vector<bool>> dp (n+1, vector<bool> (m+1, false));
  dp[0][0] = true;

  vector<vector<bool>> converted (n + 1, vector<bool> (m+1, false));
  vector<bool> b_contains_lower(m + 1, false);
  
  if (b.length()) {
    b_contains_lower[0] = islower(b[0]);
    for (int i = 1; i < m; ++i) {
      b_contains_lower[i] = b_contains_lower[i-1] || islower(b[i]);
    }
    b_contains_lower[m] = b_contains_lower[m-1];
  }

  for (int i = 0; i < a.length(); ++i) {
    for (int j = 0; j <= b.length(); ++j) {
      if (dp[i][j]) {

        if (j < b.length()) {
          if (islower(a[i]) && islower(b[j]) && a[i] == b[j] && i == j && !converted[i][j]) {
            dp[i+1][j+1] = true;
          } 
          else if (islower(a[i]) && toupper(a[i]) == b[j] && !b_contains_lower[j]) {
            converted[i+1][j+1] = true;
            dp[i+1][j+1] = true;
          }
          else if (isupper(a[i]) && a[i] == b[j]) {
            dp[i+1][j+1] = true;
          }
        }

        if (!isupper(a[i]) && !b_contains_lower[j]) {
          dp[i+1][j] = true;
           
        }
      }
    }
  }
  return dp[n][m];
}
