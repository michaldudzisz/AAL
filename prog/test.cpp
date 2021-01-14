#include <cassert>
#include <iostream> 
#include "test.h"

using namespace std;

void run_tests(bool(*f)(string, string)) {
    cout << "start tests" << endl; 
    assert(f("a", "A"));
    assert(f("a", "a"));
    assert(!f("bb", "b"));
    assert(!f("b", "a"));
    assert(f("aA", "AA"));
    assert(f("Bb", "Bb"));
    assert(!f("bb", "Bb"));
    assert(!f("bb", "bB"));
    assert(!f("aAa", "aaA"));
    assert(f("aAaAa", "AAAAA"));
    assert(!f("BbbB", "BBbB"));
    assert(f("BbBB", "BBBB"));
    assert(f("BbBb", "BB"));
    assert(!f("abcXm", "Xm"));
    assert(!f("GX", "X"));
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
    assert(f("abXXdd", "AXX"));
    assert(f("Aa", "A"));
    assert(f("aAa", "A"));
    assert(f("bAc", "A"));
    assert(!f("abcBx", "abcBX"));
    assert(f("aaaXbbbddCffE", "XCE"));
    assert(!f("Xge", "Xg"));
    
    cout << "Ok" << endl; }

