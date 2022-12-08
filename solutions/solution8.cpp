#include "solutions.h"
#include "solution8.h"

#include <numeric>

#include <iostream>

auto print(const Utils::Grid<ROWS, COLS>& g) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            std::cout << g[r][c];
        }
        std::cout << std::endl;
    } 
    std::cout << std::endl;
}

auto Solutions::solution8() -> Answers {

    Utils::Grid<ROWS, COLS> trees = Utils::readGrid<ROWS, COLS>("inputs/input8.txt");

    Utils::Grid<ROWS, COLS> maxFromLeft, maxFromRight, maxFromTop, maxFromBottom;

    for (int r = 0; r < ROWS; ++r) {
        std::array<int, COLS>& curRow = trees[r];
        std::inclusive_scan(
            curRow.cbegin(), curRow.cend(),
            maxFromLeft[r].begin(),
            Utils::max
        );

        std::inclusive_scan(
            curRow.crbegin(), curRow.crend(),
            maxFromRight[r].rbegin(),
            Utils::max
        );
    }

    for (int c = 0; c < COLS; ++c) {
        maxFromTop[0][c] = trees[0][c];
        maxFromBottom[ROWS-1][c] = trees[ROWS - 1][c];

        for (int r = 1; r < ROWS; ++r) {
            maxFromTop[r][c] = std::max(maxFromTop[r-1][c], trees[r][c]);
            maxFromBottom[ROWS - 1 -r][c] = std::max(maxFromBottom[ROWS - r][c], trees[ROWS - 1 -r][c]);
        }
    }

    int answerA = countVisibleTrees(trees, maxFromLeft, maxFromRight, maxFromTop, maxFromBottom);

    return { std::to_string(answerA), "" };
}