#include "read.h"

#include <fstream>

std::vector<std::string> Utils::readLines(const char* path) {
    std::vector<std::string> output;

    std::ifstream fileIn(path);
    for (std::string line; std::getline(fileIn, line);) {
        output.push_back(line);
    }

    return output;
}