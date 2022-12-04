#include "solutions.h"

#include "../utils/read.h"

#include <functional>
#include <numeric>
#include <utility>
#include <sstream>

#include <iostream>

struct Bounds {
    int lower;
    int upper;
};

auto boundsFromLine(const std::string& line) -> std::pair<Bounds, Bounds> {
    Bounds bounds1{}, bounds2{};
    
    char _char{};
    std::stringstream ss(line);
    ss >> bounds1.lower >> _char >> bounds1.upper >> _char
       >> bounds2.lower >> _char >> bounds2.upper;
    
    return {bounds1, bounds2};
}

auto contains(const Bounds& outer, const Bounds& inner) {
    return outer.lower <= inner.lower
        && outer.upper >= inner.upper;
}

auto Solutions::solution4() -> Answers {
    auto inputs = Utils::readLines("inputs/input4.txt");
    
    int answerA = std::transform_reduce(
        inputs.cbegin(), inputs.cend(),
        0,
        std::plus{},
        [](const auto& line){
            const auto& [bounds1, bounds2] = boundsFromLine(line);
            return (contains(bounds1, bounds2) || contains(bounds2, bounds1))
                ? 1
                : 0;
        }
    );

    return {answerA, 0};
}