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
#include <fstream>

#include "yaml-cpp/yaml.h"



const int DEFAULT_CASE_NR = 1;
const int DEFAULT_B_LENGTH = 10;
const double DEFAULT_MAX_A_FACTOR = 2;          // how many times is max a longer than b (a_max = b * maxAFactor_;)

/*
const int CASES_NR = 1;

const double B_LOWERCASE_PROBABILITY = 0.01;

const double A_LOWERCASE_PROBABILITY = 0.99;
const int A_LONGER_B_MIN = 0;
const int A_LONGER_B_STEP = 5;
const int A_LONGER_B_MAX = 50;
*/



class InvalidCallException : public std::exception {
public:

    const char* what() const throw() {
        return "Invalid call";
    };

};



class Config {
public:


    inline static bool outputToFile_;


    Config() = delete;
    Config(Config&) = delete;
    

    inline static void saveCallParams(int argc, char * argv[]) {

        // fill with default value
        caseNr_ = DEFAULT_CASE_NR;

        for (int i = 1; i < argc; i++) {
            // -<option> <argument>:
            if ((argv[i][0] == '-' || argv[i][0] == '/') && std::string(argv[i]).length() == 2) {       // unix and windows passing options conventions 
                switch (argv[i][1]) {
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
                        try {
                            caseNr_ = std::stoi(std::string(argv[i]));
                        } catch (std::exception& e) {
                            throw InvalidCallException();
                        }
                        break;
                    default:
                        throw InvalidCallException();
                        break;
                }
            } else {
                throw InvalidCallException();
            }
        }
    }



    inline static void parseConfigFile(std::string filename) {

        YAML::Node yaml_config;

        yaml_config = YAML::LoadFile(filename);

        bLength_ = yaml_config["bLength"].as<int>();
        minAFactor_ = yaml_config["minAFactor"].as<double>();
        maxAFactor_ = yaml_config["maxAFactor"].as<double>();
        aStep_ = yaml_config["aStep"].as<int>();
        aLowercaseProbability_ = yaml_config["aLowercaseProbability"].as<double>();
        bLowercaseProbability_ = yaml_config["bLowercaseProbability"].as<double>();
    }




    inline static char generateChar(double lowercase_probability) {

        char c;
        bool is_lower = ( ((double) std::rand() / RAND_MAX) <= lowercase_probability ) ? true : false;
        if (is_lower) {
            c = 'a' + (std::rand() % ('z' - 'a'));
        } else {
            c = 'A' + (std::rand() % ('Z' - 'A'));
        }

        return c;
    }



    inline static std::string generateStringB(int b_length) {

        std::string s = std::string();

        for (int i = 0; i < b_length; i++) 
            s.push_back(generateChar(bLowercaseProbability_));
        
        return s;
    }





    inline static std::string generateStringA(const std::string& b) {

        std::string a = std::string(b);
        // minALength + rand(0, maxA - b.length(), aStep):
        int a_longer_b = ( (int) (b.length() * minAFactor_) ) + (std::rand() % (int) ( ( ( (int) (b.length() * maxAFactor_) ) - b.length() ) / aStep_)) * aStep_;


        int where_to_insert;
        for (int i = 0; i < a_longer_b; i++) {
            where_to_insert = std::rand() % a.length();
            a.insert(a.begin() + (std::rand() % a.length()), generateChar(aLowercaseProbability_));
        }

        return a;
    }




    inline static void generateToFile() {

        std::ofstream file;
        std::string a, b;

        file.open(fileName_, std::ios::trunc);

        for (int i = 0; i < caseNr_; i++) {

            b = generateStringB(bLength_);
            a = generateStringA(b);

            file << a << " " << b << std::endl;
        }

        file.close();
    }




    inline static void generateToDefaultOutput() {

        std::string a, b;

        for (int i = 0; i < caseNr_; i++) {

            b = generateStringB(bLength_);
            a = generateStringA(b);

            std::cout << a << " " << b << std::endl;
        }
    }


private:


    inline static std::string fileName_;
    inline static int caseNr_;
    inline static int bLength_;
    inline static double maxAFactor_;                     // how many times is max a longer than b (a_max = b * maxAFactor_;)
    inline static double minAFactor_;
    inline static int aStep_;
    inline static double aLowercaseProbability_;
    inline static double bLowercaseProbability_;


};









int main(int argc, char * argv[]) {

    std::srand(std::time(nullptr));

    try {
        Config::saveCallParams(argc, argv);
    } catch (InvalidCallException& e) {
        std::cout << e.what() << std::endl << "Potem zrobie jakis plik z opisem wywolania." << std::endl;
        return 0;
    }

    try {
        Config::parseConfigFile("test-gen-config.yaml");
    } catch (std::exception& e) {
        std::cout << "Loading yaml file - " << e.what() << std::endl;
        return 0;
    }


    if (Config::outputToFile_)
        Config::generateToFile();
    else
        Config::generateToDefaultOutput();

    return 0;
}

