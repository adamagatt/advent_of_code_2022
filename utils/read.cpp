#include "read.h"

auto Utils::parseIntChar(char c) -> int {
    return c - '0';
}

auto Utils::readLines(const char* path) -> std::vector<std::string>{
    std::vector<std::string> output;

    std::ifstream fileIn(path);
    for (std::string line; std::getline(fileIn, line);) {
        output.push_back(line);
    }

    return output;
}