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
#include "yaml-cpp/yaml.h"

const int DEFAULT_CASE_NR = 1;
const int DEFAULT_B_LENGTH = 10;
const double DEFAULT_MAX_A_FACTOR = 2;          // how many times is max a longer than b (a_max = b * maxAFactor_;)

const int CASES_NR = 1;

const double B_LOWERCASE_PROBABILITY = 0.01;

const double A_LOWERCASE_PROBABILITY = 0.99;
const int A_LONGER_B_MIN = 0;
const int A_LONGER_B_STEP = 5;
const int A_LONGER_B_MAX = 50;


class Config {
public:

    bool outputToFile_;
    std::string fileName_;
    int caseNr_;
    int bLength_;
    double maxAFactor_;                         // how many times is max a longer than b (a_max = b * maxAFactor_;)


    void parseConfigFile(std::string filename) {

        YAML::Node yaml_config;
        try {
            yaml_config = YAML::LoadFile(filename);
        } catch (YAML::ParserException& e) {
            throw "No \"" + filename + "\" file found";
        }

        this -> bLength_ = yaml_config["bLength"].as<int>();
        this -> maxAFactor_ = yaml_config["maxAFactor"].as<double>();
    }



    void saveCallParams(int argc, char * argv[]) {

        // fill with default value
        caseNr_ = DEFAULT_CASE_NR;

        for (int i = 1; i < argc; i++) {
            if ((argv[i][0] == '-' || argv[i][0] == '/') && sizeof(argv[i]) == 2) {       // unix and windows passing options conventions 
                switch (argv[i][1]) {
                    case 'f':
                        i++;
                        if (i == argc)
                            throw "Invalid call";
                        outputToFile_ = true;
                        fileName_ = std::string(argv[i]);
                        break;
                    case 'n':
                        i++;
                        if (i == argc)
                            throw "Invalid call";
                        try {
                            caseNr_ = std::stoi(std::string(argv[i]));
                        } catch (std::exception& e) {
                            throw "Invalid call";
                        }
                        break;
                    default:
                        throw "Invalid call";
                        break;
                }
            }
        }
    }

};






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





std::string generateStringB(int b_length) {

    std::string s = std::string();

    for (int i = 0; i < b_length; i++) 
        s.push_back(generateChar(B_LOWERCASE_PROBABILITY));
    
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
    Config config = Config();

    try {
        config.saveCallParams(argc, argv);
    } catch(std::string& s) {
        std::cout << s << std::endl << "Potem zrobie jakis plik z opisem wywolania." << std::endl;
        return 0;
    }

    config.parseConfigFile("test-gen-config.yaml");


    for (int i = 0; i < CASES_NR; i++) {

        b = generateStringB(config.bLength_);
        a = generateStringA(&b);

        std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
    }

    return 0;
}

