#include "solutions/solutions.h"

#include <iostream>

int main() {

    auto solution = Solutions::selectSolution();
    auto [answerA, answerB] = solution();
    std::cout << answerA << " " << answerB << std::endl;

    return 0;
}