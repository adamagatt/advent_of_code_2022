#include <iostream>
#include <numeric>

#include "utils/read_utils.h"

int main() {
    auto lines = ReadUtils::lines("inputs/input1.txt");

    std::vector<int> largestThree(3, 0);

    int currentTotal = 0;
    for (const auto& line : lines) {
        if (!line.empty()) {
            currentTotal += std::stoi(line);
        } else {
            auto position = std::lower_bound(largestThree.cbegin(), largestThree.cend(), currentTotal);
            if (position != largestThree.cbegin()) {
                largestThree.insert(position, currentTotal);
                largestThree.erase(largestThree.cbegin());
            }
            currentTotal = 0;
        }
    }

    int answerA = *std::prev(largestThree.cend());
    int answerB = std::accumulate(largestThree.cbegin(), largestThree.cend(), 0);

    std::cout << answerA << " " << answerB << std::endl;

    return 0;
}