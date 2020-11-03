#include "algo.h"
#include <iostream>
#include <cassert>

using namespace std;

bool bf(string, string);
bool solve_lin(string, string);
void run_tests(bool(*)(string, string));

bool solve_lin(string a, string b) {
    bool b_contains_lower = false; 
    int j = 0;
    for(int i = 0; i < b.length(); ++i, ++j) {
        if (islower(b[i])) b_contains_lower = true;
        for (; j < a.length() && a[j] != b[i] && toupper(a[j]) != b[i]; ++j)
            if (isupper(a[j]) || b_contains_lower) return false;
        if (j == a.length()) return false;
    }
    for (; j < a.length(); ++j) if (isupper(a[j]) || b_contains_lower) return false;
    return true;
}


string del_low_case(string& s);
bool helper(const string& b, string s, int i);

bool bf(string a, string b) {
    if (a == b) return true;
    return helper(b, a, 0);
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

string del_low_case (string& s) {
    string ans = "";
    for (const char& ch : s) if(isupper(ch)) ans += ch;
    return ans;
}

void run_tests(bool(*f)(string, string)) {
    assert(f("a", "a"));
    assert(!f("b", "a"));
    assert(f("a", ""));
    assert(f("AkLKl", "ALK"));
    assert(f("magda", "magda"));
    assert(!f("eeewka", "ewka"));
    assert(!f("ewwka", "ewka"));
    assert(f("ANDZEJ", "ANDZEJ"));
    assert(f("andzej", "ANDZEJ"));
    assert(f("AZeaj", "AZJ"));
    assert(!f("AZej", "AZe"));
    assert(!f("ae", "a"));
    assert(!f("AZe", "Aze"));
    assert(!f("AZe", "AzE"));
    assert(!f("ad", "AB"));
    assert(!f("ada", "adb"));
    assert(!f("ada", "ADB"));
    assert(!f("", "a"));
    assert(!f("andej", "andejduda"));
}

