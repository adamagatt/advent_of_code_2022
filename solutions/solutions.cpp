#include "solutions.h"

#include <iostream>
#include <string>
#include <unordered_map>

const std::unordered_map<int, std::function<Solutions::Answers()>> solutionForChoice {
    {1, Solutions::solution1},
    {2, Solutions::solution2},
    {3, Solutions::solution3},
    {4, Solutions::solution4},
};

auto Solutions::selectSolution() -> std::function<Answers()> {
    int choice = 0;
    std::string toNewLine;
    while (!solutionForChoice.contains(choice)) {
        std::cout << "Choose a solution (1-" << MAX << "):" << std::endl;
        std::cin >> choice;
        std::cin.clear(); // Clear and ignore until newline in case of non-integral input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return solutionForChoice.at(choice);
}