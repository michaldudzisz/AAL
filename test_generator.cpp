/*
 *  AAL Projekt
 * 
 *  Generator danych testowych
 * 
 *  Michał Kruk
 *  Michał Dudzisz 
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int CASES_NR = 1;

const double B_LOWERCASE_PROBABILITY = 0.01;
const int B_MIN_LENGTH = 50;
const int B_MAX_LENGTH = 30;

const double A_LOWERCASE_PROBABILITY = 0.99;
const int A_LONGER_B_MIN = 0;
const int A_LONGER_B_STEP = 5;
const int A_LONGER_B_MAX = 50;



char generateChar(double lowercase_probability) {
    char c;
    bool is_lower = ( ((double) std::rand() / RAND_MAX) <= lowercase_probability ) ? true : false;
    if (is_lower) {
        c = 'a' + (std::rand() % ('z' - 'a'));
    } else {
        c = 'A' + (std::rand() % ('Z' - 'A'));
    }
    return c;
}

std::string generateStringB() {
    std::string s = std::string();

    int s_length = B_MIN_LENGTH + std::rand() % (B_MAX_LENGTH - B_MIN_LENGTH);
    for (int i = 0; i < s_length; i++) {
        s.push_back(generateChar(B_LOWERCASE_PROBABILITY));
    }
    return s;
}

std::string generateStringA(const std::string * const b_ptr) {
    std::string a = std::string(* b_ptr);
    int a_longer_b = A_LONGER_B_MIN + (std::rand() % ((int) (A_LONGER_B_MAX - A_LONGER_B_MIN) / A_LONGER_B_STEP)) * A_LONGER_B_STEP;
    int where_to_insert;
    for (int i = 0; i < a_longer_b; i++) {
        where_to_insert = std::rand() % a.length();
        a.insert(a.begin() + (std::rand() % a.length()), generateChar(A_LOWERCASE_PROBABILITY));
    }
    return a;
}

int main(int argc, char * argv[]) {
    std::srand(std::time(nullptr));
    std::string a, b;

    for (int i = 0; i < CASES_NR; i++) {
        b = generateStringB();
        a = generateStringA(&b);
    }

    std::cout << "a: " << a << std::endl << "b: " << b << std::endl;

    return 0;
}

