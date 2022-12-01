#include "read_utils.h"

std::vector<std::string> ReadUtils::lines(const char* path) {
    std::vector<std::string> output;

    std::ifstream fileIn(path);
    for (std::string line; std::getline(fileIn, line);) {
        output.push_back(line);
    }

    return output;
}