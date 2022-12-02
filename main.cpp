#include "solutions.h"

#include <iostream>
#include <string>

int selectProblem() {
    int choice = 0;
    std::string toNewLine;
    while (choice < 1 || choice > Solutions::MAX) {
        std::cout << "Choose a problem (1-" << Solutions::MAX << "):" << std::endl;
        std::cin >> choice;
        std::cin.clear(); // Clear and ignore until newline in case of non-integral input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}

int main() {

    int choice = selectProblem();

    auto solution = (choice == 1) ? Solutions::Solution1 : (choice == 2) ? Solutions::Solution2 : nullptr;

    if (solution != nullptr) {
        auto [answerA, answerB] = solution();
        std::cout << answerA << " " << answerB << std::endl;
    }

    return 0;
}