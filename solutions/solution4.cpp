#include "solutions.h"

#include "../utils/read.h"

#include <algorithm>
#include <utility>
#include <sstream>

struct Bounds {
    int lower;
    int upper;
};

auto boundsFromText(const std::string& text) -> std::pair<Bounds, Bounds> {
    Bounds bounds1{}, bounds2{};
    
    char _char{};
    std::stringstream ss(text);
    ss >> bounds1.lower >> _char >> bounds1.upper >> _char
       >> bounds2.lower >> _char >> bounds2.upper;
    
    return {bounds1, bounds2};
}

auto contains(const Bounds& outer, const Bounds& inner) -> bool {
    return outer.lower <= inner.lower
        && outer.upper >= inner.upper;
}

auto eitherContainsTheOther(const std::pair<Bounds, Bounds>& pair) -> bool {
    return contains(pair.first, pair.second)
        || contains(pair.second, pair.first);
}

auto overlaps(const std::pair<Bounds, Bounds>& pair) -> bool {
    return pair.first.lower <= pair.second.upper
        && pair.second.lower <= pair.first.upper;
}

auto Solutions::solution4() -> Answers {
    auto inputs = Utils::readLines("inputs/input4.txt");
    
    std::vector<std::pair<Bounds, Bounds>> boundsPairs(inputs.size());
    std::ranges::transform(inputs, boundsPairs.begin(), boundsFromText);

    int answerA = std::ranges::count_if(boundsPairs, eitherContainsTheOther);

    int answerB = std::ranges::count_if(boundsPairs, overlaps);

    return { std::to_string(answerA), std::to_string(answerB) };
}