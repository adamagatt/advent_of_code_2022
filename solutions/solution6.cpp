#include "solutions.h"

#include "../utils/read.h"

#include <algorithm>
#include <string>
#include <unordered_map>

using Counter = std::unordered_map<char, int>;

auto anyRepeatedChars(const Counter& counter) -> bool {
    return std::ranges::any_of(
        counter,
        [](const auto& keyValue) {
            return keyValue.second > 1;
        }
    );
}

auto buildCounter(const auto& trailingIt, const auto& leadingIt) -> Counter {
    Counter output;

    for (auto it = trailingIt; it != leadingIt; ++it) {
        char c = *it;
        output[c] += 1;
    }
    // leading iterator is included (not past range like end iterators)
    ++output[*leadingIt];

    return output;
}

auto updateCounter(Counter& counter, const auto& trailingIt, const auto& leadingIt ) {
    // Add the char ABOUT to enter the window
    char addChar = *std::next(leadingIt);
    ++counter[addChar];
    
    // Remove the char JUST leaving the window
    char removeChar = *trailingIt;
    --counter[removeChar];
}

auto answerForWindowSize(const std::string& input, const int windowSize) -> int {
    auto trailingIt = input.cbegin();
    // leading is end-of-window, not one past like end iterators
    auto leadingIt = std::next(trailingIt, windowSize - 1);
    Counter counter = buildCounter(trailingIt, leadingIt);

    int answer = windowSize; // Marker position is counted from end of window
    for ( ; anyRepeatedChars(counter); ++trailingIt, ++leadingIt, ++answer) {
        updateCounter(counter, trailingIt, leadingIt);
    }

    return answer;
}

auto Solutions::solution6() -> Answers {
    std::string input = Utils::readLines("inputs/input6.txt").at(0);

    int answerA = answerForWindowSize(input, 4);
    int answerB = answerForWindowSize(input, 14);

    return { std::to_string(answerA), std::to_string(answerB) };
}