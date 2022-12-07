#ifndef __READ_H
#define __READ_H

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace Utils {
    [[nodiscard]] auto readLines(const char* path) -> std::vector<std::string>;

    template <size_t N>
    [[nodiscard]] auto readTokens(const char* path) -> std::vector<std::array<std::string, N>> {
        std::vector<std::array<std::string, N>> output;

        std::ifstream fileIn(path);
        for (std::string line; std::getline(fileIn, line);) {
            std::stringstream ss(line);
            std::array<std::string, N> tokens;
            for (int i = 0; i < N; ++i) {
                ss >> tokens[i];
            }
            output.push_back(tokens);
        }

        return output;
    }
}

#endif