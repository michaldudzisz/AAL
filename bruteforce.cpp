#include <string>
#include <iostream>

bool containLowercaseLetter(std::string s) {
    for (char c : s) {
        if (std::islower(c))
            return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    // argumenty wywolania:
    std::string a, b;
    a = std::string(argv[1]);
    b = std::string(argv[2]);

    // jesli b zawiera male litery
    if (containLowercaseLetter(b)) {
        std::cout << "false" << std::endl;
        return 0;
    }

    std::string::iterator aIt = a.begin();
    std::string::iterator bIt = b.begin();
    while (aIt != a.end() && bIt != b.end()) {
        // capitalise(*aIt), zeby moc porownac dowolna *aIt z na pewno wielka *bIt
        if (std::toupper(*aIt) == *bIt)
            bIt++;

        aIt++;
    }

    if (bIt == b.end())
        std::cout << "true" << std::endl;
    else 
        std::cout << "false" << std::endl;
    

    return 0;
}

