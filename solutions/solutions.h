#ifndef __SOLUTIONS_H
#define __SOLUTIONS_H

#include <functional>
#include <string>
#include <utility>

namespace Solutions {
    using Answers = std::pair<std::string, std::string>;

    auto solution1() -> Answers;
    auto solution2() -> Answers;
    auto solution3() -> Answers;
    auto solution4() -> Answers;
    auto solution5() -> Answers;
    auto solution6() -> Answers;
    auto solution7() -> Answers;

    constexpr int MAX = 7;

    auto selectSolution() -> std::function<Answers()> ;
}

#endif