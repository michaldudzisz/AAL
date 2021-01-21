/*
 *  AAL Projekt
 * 
 *  Generator danych testowych
 * 
 *  Michał Kruk
 *  Michał Dudzisz 
 */

#ifndef TEST_GENERATOR_H
#define TEST_GENERATOR_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <random>

#include "yaml-cpp/yaml.h"

class InvalidCallException : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Invalid call";
    };
};

class TestGenerator
{
public:
    static TestGenerator *getInstance();

    TestGenerator(TestGenerator &) = delete;
    TestGenerator operator=(TestGenerator &) = delete;

    void run();
    void saveCallParams(int argc, char *argv[]);
    void parseConfigFile(std::string filename);

private:
    TestGenerator();
    void initializeRNG();
    char generateChar(double lowercase_probability);
    std::string generateStringB(int b_length);
    std::string generateStringA(const std::string &b);
    void generateToFile();
    void generateToDefaultOutput();

    static TestGenerator *instance_;

    bool caseNrSpecifiedFromCmd_ = false;
    bool fixedAMode_ = false;
    bool fixedBMode_ = false;
    bool pyramidMode_ = false;
    bool outputToFile_ = false;
    std::string fileName_;
    int caseNr_;
    int bLength_;
    double maxAFactor_;
    double minAFactor_;
    double maxBFactor_;
    int aStep_;
    int bStep_;
    double aLowercaseProbability_;
    double bLowercaseProbability_;
    double bToLowerProbability_;

    std::mt19937 generator_;

    std::uniform_int_distribution<std::mt19937::result_type> a_longer_b_distrib_;
    std::uniform_int_distribution<char> characterDistribution_ =
        std::uniform_int_distribution<char>('a', 'z');
    std::uniform_real_distribution<double> probabilityDistribution_ =
        std::uniform_real_distribution<double>(0, 1);

    const int DEFAULT_CASE_NR = 1;
};

#endif