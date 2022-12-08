#ifndef __SOLUTION8_H_
#define __SOLUTION8_H_

#include "../utils/read.h"

constexpr int ROWS = 99;
constexpr int COLS = 99;

template <size_t R, size_t C>
auto countVisibleTrees(
    const Utils::Grid<R, C>& trees,
    const Utils::Grid<R, C>& maxFromLeft,
    const Utils::Grid<R, C>& maxFromRight,
    const Utils::Grid<R, C>& maxFromTop,
    const Utils::Grid<R, C>& maxFromBottom
) -> int {

    // All outside trees are always visible
    int visible = 2 * (ROWS + COLS - 2);

    for (int r = 1; r < (ROWS - 1); ++r) {
        for (int c = 1; c < (COLS - 1); ++c) {
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

#endif