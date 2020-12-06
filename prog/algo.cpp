#include "algo.h"
#include <iostream>
using namespace std;

bool solver_a(string a, string b) {
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
