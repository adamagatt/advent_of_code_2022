#ifndef __READ_H
#define __READ_H

#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace Utils {
    [[nodiscard]] auto parseIntChar(char c) -> int;

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

    template <size_t C>
    using Row = std::array<int, C>;

    template <size_t R, size_t C>
    using Grid = std::array<Row<C>, R>;

    template <size_t R, size_t C>
    auto readGrid(const std::string& path) -> Grid<R, C> {
        Grid<R, C> grid;

        std::ifstream fileIn(path);

        std::array<int, C>* row = grid.begin();
        for (std::string line; std::getline(fileIn, line); ++row) {
            std::ranges::transform(line, row->begin(), parseIntChar);
        }

        return grid;
    }
}

#endif