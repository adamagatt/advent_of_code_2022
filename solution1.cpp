#include "solutions.h"

#include <algorithm>
#include <deque>
#include <numeric>

#include "utils/read_utils.h"

auto Solutions::Solution1() -> Answers {
    auto lines = ReadUtils::lines("inputs/input1.txt");

    std::deque<int> largestThree(3, 0);

    int currentTotal = 0;
    for (const auto& line : lines) {
        if (!line.empty()) {
            currentTotal += std::stoi(line);
        } else {
            auto position = std::ranges::lower_bound(largestThree, currentTotal);
            if (position != largestThree.cbegin()) {
                largestThree.insert(position, currentTotal);
                largestThree.pop_front();
            }
            currentTotal = 0;
        }
    }

    int answerA = *std::prev(largestThree.cend());
    int answerB = std::accumulate(largestThree.cbegin(), largestThree.cend(), 0);

    return {answerA, answerB};
}