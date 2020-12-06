#include <cassert>
#include <iostream> 
#include "test.h"

using namespace std;

void run_tests(bool(*f)(string, string)) {
    cout << "start tests" << endl; 
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
    assert(f("bB", "B"));
    assert(!f("abcBx", "abcBX"));
    cout << "Ok" << endl;
}

