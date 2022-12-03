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

auto Solutions::Solution3() -> Answers {
    auto inputs = ReadUtils::lines("inputs/input3.txt");

    int answerA = std::transform_reduce(
        inputs.cbegin(), inputs.cend(),
        0, // init
        std::plus{},
        priorityOfDoubledItem
    );

    return {answerA, 0};
}