#ifndef __SOLUTION8_H_
#define __SOLUTION8_H_

#include "../utils/read.h"

constexpr size_t ROWS = 99;
constexpr size_t COLS = 99;

auto solvePartA(const Utils::Grid<ROWS, COLS>& trees) -> int;

auto countVisibleTrees(
    const Utils::Grid<ROWS, COLS>& trees,
    const Utils::Grid<ROWS, COLS>& maxFromLeft,
    const Utils::Grid<ROWS, COLS>& maxFromRight,
    const Utils::Grid<ROWS, COLS>& maxFromTop,
    const Utils::Grid<ROWS, COLS>& maxFromBottom
) -> int;

auto solvePartB(const Utils::Grid<ROWS, COLS>& trees) -> int;

auto scoreForTree(const Utils::Grid<ROWS, COLS>& trees, size_t r, size_t c) -> int;

#endif