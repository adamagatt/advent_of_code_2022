#include "solutions.h"

#include "utils/read_utils.h"

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

    auto findItem = std::find_if(halfway, line.cend(), [&left](char c) {return left.contains(c);});
    if (findItem != line.cend()) {
        return priority(*findItem);
    } else {
        return -1;
    }
}

auto presentInThreePacks(const std::string& elf1, const std::string& elf2, const std::string& elf3) -> char {
    std::unordered_set<char> presentInOne {elf1.cbegin(), elf1.cend()};

    std::unordered_set<char> presentInTwo;
    std::copy_if(
        elf2.cbegin(), elf2.cend(),
        std::inserter(presentInTwo, presentInTwo.end()),
        [&presentInOne](char c){return presentInOne.contains(c);}
    );

    auto presentInThree = std::find_if(
        elf3.cbegin(), elf3.cend(),
        [&presentInTwo](char c){return presentInTwo.contains(c);}
    );

    return *presentInThree; // Note: No handling at all of failure case; assumes input is valid
}

auto Solutions::Solution3() -> Answers {
    auto inputs = ReadUtils::lines("inputs/input3.txt");

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