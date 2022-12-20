#ifndef __SOLUTION4_H_
#define __SOLUTION4_H_

#include <string>
#include <utility>

struct Bounds {
    int lower;
    int upper;
};

using BoundsPair = std::pair<Bounds, Bounds>;

auto boundsFromText(const std::string& text) -> BoundsPair;

auto contains(const Bounds& outer, const Bounds& inner) -> bool;

auto eitherContainsTheOther(const BoundsPair& pair) -> bool;

auto overlaps(const BoundsPair& pair) -> bool;

#endif