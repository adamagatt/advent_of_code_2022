#include "solutions.h"
#include "solution8.h"

#include <numeric>

auto Solutions::solution8() -> Answers {

    const Utils::Grid<ROWS, COLS> trees = Utils::readGrid<ROWS, COLS>("inputs/input8.txt");

    int answerA = solvePartA(trees);
    int answerB = solvePartB(trees);

    return { std::to_string(answerA), std::to_string(answerB) };
}

auto solvePartA(const Utils::Grid<ROWS, COLS>& trees) -> int {

    Utils::Grid<ROWS, COLS> maxFromLeft, maxFromRight, maxFromTop, maxFromBottom;

    for (size_t r = 0; r < ROWS; ++r) {
        const std::array<int, COLS>& curRow = trees[r];
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

    for (size_t c = 0; c < COLS; ++c) {
        maxFromTop[0][c] = trees[0][c];
        maxFromBottom[ROWS-1][c] = trees[ROWS - 1][c];

        for (size_t r = 1; r < ROWS; ++r) {
            maxFromTop[r][c] = std::max(maxFromTop[r-1][c], trees[r][c]);
            maxFromBottom[ROWS - 1 -r][c] = std::max(maxFromBottom[ROWS - r][c], trees[ROWS - 1 -r][c]);
        }
    }

    return countVisibleTrees(trees, maxFromLeft, maxFromRight, maxFromTop, maxFromBottom);
}

auto countVisibleTrees(
    const Utils::Grid<ROWS, COLS>& trees,
    const Utils::Grid<ROWS, COLS>& maxFromLeft,
    const Utils::Grid<ROWS, COLS>& maxFromRight,
    const Utils::Grid<ROWS, COLS>& maxFromTop,
    const Utils::Grid<ROWS, COLS>& maxFromBottom
) -> int {

    // All outside trees are always visible
    int visible = 2 * (ROWS + COLS - 2);

    for (size_t r = 1; r < (ROWS - 1); ++r) {
        for (size_t c = 1; c < (COLS - 1); ++c) {
            int treeHeight = trees[r][c];
            if (maxFromLeft[r][c-1] < treeHeight
             || maxFromRight[r][c+1] < treeHeight
             || maxFromTop[r-1][c] < treeHeight
             || maxFromBottom[r+1][c] < treeHeight) {
                visible++;
            }
        }
    }

    return visible;
}

auto solvePartB(const Utils::Grid<ROWS, COLS>& trees) -> int {
    int bestScore = 0;

    for (size_t r = 1; r < (ROWS - 1); ++r) {
        for (size_t c = 1; c < (COLS - 1); ++c) {
            bestScore = std::max(bestScore, scoreForTree(trees, r, c));
        }
    }
    return bestScore;
}

auto scoreForTree(const Utils::Grid<ROWS, COLS>& trees, size_t tr, size_t tc) -> int {
    const int curHeight = trees[tr][tc];

    int leftBlocker = 0;
    for (int c = tc-1; c > 0; --c) {
        if (trees[tr][c] >= curHeight) {
            leftBlocker = c;
            break;
        }
    }
    int leftFactor = tc - leftBlocker;

    int rightBlocker = COLS - 1;
    for (int c = tc+1; c < COLS - 1; ++c) {
        if (trees[tr][c] >= curHeight) {
            rightBlocker = c;
            break;
        }
    }
    int rightFactor = rightBlocker - tc;

    int topBlocker = 0;
    for (int r = tr-1; r > 0; --r) {
        if (trees[r][tc] >= curHeight) {
            topBlocker = r;
            break;
        }
    }
    int topFactor = tr - topBlocker;

    int bottomBlocker = ROWS - 1;
    for (int r = tr+1; r < ROWS - 1; ++r) {
        if (trees[r][tc] >= curHeight) {
            bottomBlocker = r;
            break;
        }
    }
    int bottomFactor = bottomBlocker - tr;

    return leftFactor * rightFactor * topFactor * bottomFactor;
}