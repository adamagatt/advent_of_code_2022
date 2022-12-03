#include "solutions.h"

#include "../utils/functional.h"
#include "../utils/read.h"

#include <algorithm>
#include <numeric>
#include <unordered_set>

int priority(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

auto priorityOfDoubledItem(const std::string& line) -> int {
    size_t num_items = line.size();
    auto halfway = std::next(line.cbegin(), num_items/2);

    std::unordered_set<char> left {line.cbegin(), halfway};

    auto findItem = std::find_if(halfway, line.cend(), Utils::inSet(left));

    return priority(*findItem); // Note: No handling at all of failure case; assumes input is valid
}

auto presentInThreePacks(const std::string& elf1, const std::string& elf2, const std::string& elf3) -> char {
    std::unordered_set<char> firstPack {elf1.cbegin(), elf1.cend()};

    std::unordered_set<char> inTwoPacks;
    std::copy_if(
        elf2.cbegin(), elf2.cend(),
        std::inserter(inTwoPacks, inTwoPacks.end()),
        Utils::inSet(firstPack)
    );

    auto inThreePacks = std::find_if(
        elf3.cbegin(), elf3.cend(),
        Utils::inSet(inTwoPacks)
    );

    return *inThreePacks; // Note: No handling at all of failure case; assumes input is valid
}

auto Solutions::Solution3() -> Answers {
    auto inputs = Utils::readLines("inputs/input3.txt");

    int answerA = std::transform_reduce(
        inputs.cbegin(), inputs.cend(),
        0, // init
        std::plus{},
        priorityOfDoubledItem
    );

    int answerB = 0;
    for (auto it = inputs.cbegin(); it < inputs.cend(); std::advance(it, 3)) {
        auto elf1 = it, elf2 = std::next(it), elf3 = std::next(it, 2);

        answerB += priority(presentInThreePacks(*elf1, *elf2, *elf3));
    }

    return {answerA, answerB};
}