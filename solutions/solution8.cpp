#include "solutions.h"
#include "solution8.h"

#include <numeric>

auto Solutions::solution8() -> Answers {
    const TreeGrid trees = Utils::readGrid<ROWS, COLS>("inputs/input8.txt");

    int answerA = solvePartA(trees);
    int answerB = solvePartB(trees);

    return { std::to_string(answerA), std::to_string(answerB) };
}


auto solvePartA(const TreeGrid& trees) -> int {

    const auto [maxFromLeft, maxFromRight] = scanRowsForMaximums(trees);
    const auto [maxFromTop, maxFromBottom] = scanColumnsForMaximums(trees);      

    return countVisibleTrees(trees, maxFromLeft, maxFromRight, maxFromTop, maxFromBottom);
}


auto scanRowsForMaximums(const TreeGrid& trees) -> std::pair<TreeGrid, TreeGrid> {
    TreeGrid maxFromLeft, maxFromRight;
    
    for (size_t r = 0; r < ROWS; ++r) {
        const TreeRow& treesInRow = trees[r];
        TreeRow& rowMaxFromLeft = maxFromLeft[r];
        TreeRow& rowMaxFromRight = maxFromRight[r];

        std::inclusive_scan(
            treesInRow.cbegin(), treesInRow.cend(),
            rowMaxFromLeft.begin(),
            std::ranges::max
        );

        std::inclusive_scan(
            treesInRow.crbegin(), treesInRow.crend(),
            rowMaxFromRight.rbegin(),
            std::ranges::max
        );
    }

    return {maxFromLeft, maxFromRight};
}


auto scanColumnsForMaximums(const TreeGrid& trees) -> std::pair<TreeGrid, TreeGrid> {
    TreeGrid maxFromTop, maxFromBottom;

    for (size_t c = 0; c < COLS; ++c) {
        maxFromTop[0][c] = trees[0][c];
        for (size_t r = 1; r < ROWS; ++r) {
            maxFromTop[r][c] = std::max(maxFromTop[r-1][c], trees[r][c]);
        }

        maxFromBottom[ROWS-1][c] = trees[ROWS - 1][c];
        for (size_t r = ROWS - 2; r > 0; --r) {
            maxFromBottom[r][c] = std::max(maxFromBottom[r+1][c], trees[r][c]);
        }
        maxFromBottom[0][c] = std::max(maxFromBottom[1][c], trees[0][c]);
    }  

    return {maxFromTop, maxFromBottom};
}


auto countVisibleTrees(
    const TreeGrid& trees,
    const TreeGrid& maxFromLeft,
    const TreeGrid& maxFromRight,
    const TreeGrid& maxFromTop,
    const TreeGrid& maxFromBottom
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


auto solvePartB(const TreeGrid& trees) -> int {
    int bestScore = 0;

    for (size_t r = 1; r < (ROWS - 1); ++r) {
        for (size_t c = 1; c < (COLS - 1); ++c) {
            bestScore = std::max(bestScore, scoreForTree(trees, r, c));
        }
    }
    return bestScore;
}


auto scoreForTree(const TreeGrid& trees, size_t tr, size_t tc) -> int {
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