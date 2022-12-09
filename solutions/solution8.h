#ifndef __SOLUTION8_H_
#define __SOLUTION8_H_

#include "../utils/read.h"

constexpr size_t ROWS = 99;
constexpr size_t COLS = 99;

using TreeGrid = Utils::Grid<ROWS, COLS>;

auto solvePartA(const TreeGrid& trees) -> int;

auto performRowScans(const TreeGrid& trees) -> std::pair<TreeGrid, TreeGrid>;
auto performColumnScans(const TreeGrid& trees) -> std::pair<TreeGrid, TreeGrid>;

auto countVisibleTrees(
    const TreeGrid& trees,
    const TreeGrid& maxFromLeft,
    const TreeGrid& maxFromRight,
    const TreeGrid& maxFromTop,
    const TreeGrid& maxFromBottom
) -> int;

auto solvePartB(const TreeGrid& trees) -> int;

auto scoreForTree(const TreeGrid& trees, size_t r, size_t c) -> int;

#endif