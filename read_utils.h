#ifndef __READ_UTILS_H
#define __READ_UTILS_H

#include <fstream>
#include <vector>
#include <string>

namespace ReadUtils {
    [[nodiscard]] inline std::vector<std::string> lines(const char* path) {
        std::vector<std::string> output;

        std::ifstream fileIn(path);
        for (std::string line; std::getline(fileIn, line); ) {
            output.push_back(line);
        }

        return output;
    }
}

#endif