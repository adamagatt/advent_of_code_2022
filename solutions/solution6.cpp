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
            // Second is value in key-value pair
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

    return output;
}

auto updateCounter(Counter& counter, const auto& trailingIt, const auto& leadingIt ) {
    // Add the char ABOUT to enter the window
    char addChar = *leadingIt;
    ++counter[addChar];
    
    // Remove the char JUST leaving the window
    char removeChar = *trailingIt;
    --counter[removeChar];
}

auto answerForWindowSize(const std::string& input, const int windowSize) -> int {
    auto trailingIt = input.cbegin();
    // Leading iterator is just past end-of-window, like an end iterator
    auto leadingIt = std::next(trailingIt, windowSize);
    Counter counter = buildCounter(trailingIt, leadingIt);

    for ( ; anyRepeatedChars(counter); ++trailingIt, ++leadingIt) {
        updateCounter(counter, trailingIt, leadingIt);
    }

    // Return how far the leading edge of the window is from the input start
    return leadingIt - input.cbegin();
}

auto Solutions::solution6() -> Answers {
    std::string input = Utils::readLines("inputs/input6.txt").at(0);

    int answerA = answerForWindowSize(input, 4);
    int answerB = answerForWindowSize(input, 14);

    return { std::to_string(answerA), std::to_string(answerB) };
}