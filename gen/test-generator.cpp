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
#include <fstream>
#include <random>
#include <cstdio>

#include "yaml-cpp/yaml.h"

#include "test-generator.h"

TestGenerator *TestGenerator::instance_ = nullptr;

TestGenerator *TestGenerator::getInstance()
{
    if (instance_ == nullptr)
        instance_ = new TestGenerator();
    return instance_;
}

TestGenerator::TestGenerator()
{
    std::random_device dev;
    generator_ = std::mt19937(dev());
}

void TestGenerator::saveCallParams(int argc, char *argv[])
{
    caseNr_ = DEFAULT_CASE_NR;

    for (int i = 1; i < argc; i++)
    {
        // -<option> <argument>:
        if ((argv[i][0] == '-' || argv[i][0] == '/') && std::string(argv[i]).length() == 2)
        {
            switch (argv[i][1])
            {
            case 'f':
                i++;
                if (i == argc)
                    throw InvalidCallException();
                outputToFile_ = true;
                fileName_ = std::string(argv[i]);
                break;
            case 'n':
                i++;
                if (i == argc)
                    throw InvalidCallException();
                    caseNrSpecifiedFromCmd_ = true;
                try
                {
                    caseNr_ = std::stoi(std::string(argv[i]));
                }
                catch (std::exception &e)
                {
                    throw InvalidCallException();
                }
                break;
            default:
                throw InvalidCallException();
                break;
            }
        }
        else
        {
            throw InvalidCallException();
        }
    }
}

void TestGenerator::parseConfigFile(std::string filename)
{
    YAML::Node yaml_config;

    yaml_config = YAML::LoadFile(filename);

    bLength_ = yaml_config["bLength"].as<int>();
    minAFactor_ = yaml_config["minAFactor"].as<double>();
    maxAFactor_ = yaml_config["maxAFactor"].as<double>();
    aStep_ = yaml_config["aStep"].as<int>();
    aLowercaseProbability_ = yaml_config["aLowercaseProbability"].as<double>();
    bLowercaseProbability_ = yaml_config["bLowercaseProbability"].as<double>();
    if (!caseNrSpecifiedFromCmd_)
        caseNr_ = yaml_config["casesToGenerate"].as<double>();
}

char TestGenerator::generateChar(double lowercase_probability)
{

    bool is_lower = (probabilityDistribution_(generator_) <= lowercase_probability) ? true : false;

    char c = characterDistribution_(generator_);

    if (!is_lower)
        c = std::toupper(c);

    return c;
}

std::string TestGenerator::generateStringB(int b_length)
{

    std::string s = std::string();

    for (int i = 0; i < b_length; i++)
        s.push_back(generateChar(bLowercaseProbability_));

    return s;
}

std::string TestGenerator::generateStringA(const std::string &b)
{
    std::string a = std::string(b);
    int a_longer_b = a_longer_b_distrib_(generator_);

    std::uniform_int_distribution<int> distrib =
        std::uniform_int_distribution<int>(0, a.length() + 1);

    int where_to_insert;
    for (int i = 0; i < a_longer_b; i++)
    {
        where_to_insert = distrib(generator_);
        const char char_to_insert = generateChar(aLowercaseProbability_);
        if (where_to_insert <= a.length())
            a.insert(a.begin() + where_to_insert, char_to_insert);
        else
            a.append(1, char_to_insert);
    }

    return a;
}

void TestGenerator::initializeRNG()
{
    int max_a_longer_b_steps = ((int)(bLength_ * maxAFactor_) - bLength_) / aStep_;
    a_longer_b_distrib_ = std::uniform_int_distribution<std::mt19937::result_type>(0, max_a_longer_b_steps);
}

void TestGenerator::generateToFile()
{

    std::ofstream file;
    std::string a, b;

    file.open(fileName_, std::ios::trunc);

    for (int i = 0; i < caseNr_; i++)
    {

        b = generateStringB(bLength_);
        a = generateStringA(b);

        file << a << " " << b << std::endl;
    }

    file.close();
}

void TestGenerator::generateToDefaultOutput()
{

    std::string a, b;

    for (int i = 0; i < caseNr_; i++)
    {

        b = generateStringB(bLength_);
        a = generateStringA(b);

        std::cout << a << " " << b << std::endl;
    }
}

void TestGenerator::run()
{
    initializeRNG();

    if (outputToFile_)
        generateToFile();
    else
        generateToDefaultOutput();
}

const char *PROPER_CALL_DESCRIPTION = 
"Test generator should be called as: \n"
"test-generetor <-f filename.txt> <-n number>\n\n"
"Where <number> is integer value of generated test cases.\n"
"Both -f and -n are optional. \nIf -f is not used, "
"test cases are printed out into default output. \n"
"If -n not used, test cases number is taken from test-gen-config.yaml file\n";


int main(int argc, char *argv[])
{

    std::srand(time(NULL));

    TestGenerator *gen = TestGenerator::getInstance();

    try
    {
        gen->saveCallParams(argc, argv);
    }
    catch (InvalidCallException &e)
    {
        std::cout << e.what() << std::endl
                  << PROPER_CALL_DESCRIPTION << std::endl;
        return 0;
    }

    try
    {
        gen->parseConfigFile("test-gen-config.yaml");
    }
    catch (std::exception &e)
    {
        std::cout << "Loading yaml file - " << e.what() << std::endl;
        return 0;
    }
    
    gen->run();

    return 0;
}


