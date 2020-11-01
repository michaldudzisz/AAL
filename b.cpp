#include <iostream>
#include <cassert>

using namespace std;

bool solve2(string, string);
void run_tests(bool(*)(string, string));

int main(/*int argc, char** argv*/) {
    run_tests(solve2);
}

void run_tests(bool(*f)(string, string)) {
    assert((f("a", "a")));
    assert(f("AkLEKl", "ALEK"));
    assert(f("magda", "magda"));
    assert(f("ANDRZEJ", "ANDRZEJ"));
    assert(f("andrzej", "ANDRZEJ"));
    assert(f("ANDRZeadfadsfdasj", "ANDRZEJ"));
}

bool solve2 (string a, string b) {
    int j = 0;
    bool b_contains_lower = false;
    for (int i = 0; i < a.length(); ++i) {
        if (islower(b[j])) b_contains_lower = true;
        if (a[i] == b[j] || toupper(a[i]) == b[j]) ++j;
        else if (isupper(a[i]) || b_contains_lower) return false;
    }
    return true;
}
