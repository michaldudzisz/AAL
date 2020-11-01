#include <iostream>
#include <cassert>

using namespace std;

bool solve2(string, string);
bool solve3(string, string);
void run_tests(bool(*)(string, string));

int main(/*int argc, char** argv*/) {
    run_tests(solve3);
}

void run_tests(bool(*f)(string, string)) {
    assert(f("a", "a"));
    assert(!f("b", "a"));
    assert(f("a", ""));
    assert(f("AkLEKl", "ALEK"));
    assert(f("magda", "magda"));
    assert(!f("eeeeewka", "ewka"));
    assert(!f("ewwka", "ewka"));
    assert(f("ANDRZEJ", "ANDRZEJ"));
    assert(f("andrzej", "ANDRZEJ"));
    assert(f("ANDRZeadfadsfdasj", "ANDRZEJ"));
    assert(!f("ad", "AB"));
    assert(!f("ada", "adb"));
    assert(!f("ada", "ADB"));
    assert(!f("", "a"));
    assert(!f("andrzej", "andrzejduda"));
}

bool solve3(string a, string b) {
    bool b_contains_lower = false; 
    for(int i = 0, j = 0; i < b.length(); ++i, ++j) {
        if (islower(b[i])) b_contains_lower = true;
        for (; j < a.length() && a[j] != b[i] && toupper(a[j]) != b[i]; ++j)
            if (isupper(a[j]) || b_contains_lower) return false;
        if (j == a.length()) return false;
    }
    return true;
}
