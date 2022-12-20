#include "solutions.h"
#include "solution3.h"

#include "../utils/functional.h"
#include "../utils/read.h"

#include <cctype>
#include <algorithm>
#include <execution>
#include <numeric>
#include <unordered_set>

auto Solutions::solution3() -> Answers {
    auto inputs = Utils::readLines("inputs/input3.txt");

    int answerA = std::transform_reduce(
        std::execution::par_unseq,
        inputs.cbegin(), inputs.cend(),
        0, // init
        std::plus{},
        [](const auto& line){return priority(doubledItem(line));}
    );

    int answerB = 0;
    for (auto it = inputs.cbegin(); it < inputs.cend(); std::advance(it, 3)) {
        const auto& elf1 = *it;
        const auto& elf2 = *std::next(it);
        const auto& elf3 = *std::next(it, 2);

        answerB += priority(presentInThreePacks(elf1, elf2, elf3));
    }

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto priority(char c) -> int {
    if (std::islower(c)) {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

auto doubledItem(const std::string& line) -> char {
    auto halfway = std::next(line.cbegin(), line.size()/2);

    std::unordered_set firstHalf {line.cbegin(), halfway};

    auto findItem = std::find_if(halfway, line.cend(), Utils::inSet(firstHalf));

    return *findItem; // Note: No handling at all of failure case; assumes input is valid
}

auto presentInThreePacks(const std::string& elf1, const std::string& elf2, const std::string& elf3) -> char {
    std::unordered_set candidates {elf1.cbegin(), elf1.cend()};

    std::unordered_set elf2Chars {elf2.cbegin(), elf2.cend()};
    std::erase_if(candidates, Utils::notInSet(elf2Chars));

    auto commonChar = std::ranges::find_if(elf3, Utils::inSet(candidates));

    return *commonChar; // Note: No handling at all of failure case; assumes input is valid
}