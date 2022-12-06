#include "solutions.h"

#include "../utils/read.h"

#include <string>

auto nextFourAllDifferent(const auto& it) -> bool {
    char pos1 = *it;
    char pos2 = *(std::next(it, 1));
    char pos3 = *(std::next(it, 2));
    char pos4 = *(std::next(it, 3));

    return pos1 != pos2 && pos1 != pos3 && pos1 != pos4
        && pos2 != pos3 && pos2 != pos4
        && pos3 != pos4;
}

auto Solutions::solution6() -> Answers {
    std::string input = Utils::readLines("inputs/input6.txt").at(0);

    int answerA = 4; // Marker position is counted from end of run of 4
    for (auto it = input.cbegin(); !nextFourAllDifferent(it); ++it, ++answerA) { }

    return { std::to_string(answerA), "" };
}