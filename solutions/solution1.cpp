#include "solutions.h"

#include <algorithm>
#include <list>
#include <numeric>

#include "../utils/read.h"

auto Solutions::solution1() -> Answers {
    auto lines = Utils::readLines("inputs/input1.txt");

    std::list largestThree(3, 0);

    for (int currentTotal = 0; const auto& line : lines) {
        if (!line.empty()) {
            currentTotal += std::stoi(line);
        } else {
            // We have a completed total. Find out where it belongs in our sorted top-three list,
            // insert it in the right position (found by lower_bound) if it qualifies. 
            auto position = std::ranges::lower_bound(largestThree, currentTotal);
            if (position != largestThree.cbegin()) {
                largestThree.insert(position, currentTotal);
                largestThree.pop_front();
            }

            // New group will start, reset total
            currentTotal = 0;
        }
    }

    // Last element in top-three list is largest
    int answerA = *largestThree.crbegin();
    int answerB = std::accumulate(largestThree.cbegin(), largestThree.cend(), 0);

    return {std::to_string(answerA), std::to_string(answerB)};
}