#include <cassert>
#include <iostream> 
#include "test.h"

using namespace std;

void run_tests(bool(f)(const string&, const string&)) {
    cout << "start tests" << endl; 
    string a;
    string b;
    a = "a"; b = "a";
    assert(f(a,b));

    a = "a"; b = "b";
    assert(!f(a,b));

    a = "aAaAaA"; b = "AAAAAA"; 
    assert(f(a,b));

    a = "aAaAaA"; b = "AAAAaA"; 
    assert(!f(a,b));

    a = "aAaAa"; b = "AAAA"; 
    assert(f(a,b));
    
    a = "aAaAa"; b = "AAAWA"; 
    assert(!f(a,b));

    cout << "Ok" << endl; }

