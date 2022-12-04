#ifndef __SOLUTIONS_H
#define __SOLUTIONS_H

#include <functional>
#include <utility>

namespace Solutions {
    using Answers = std::pair<int, int>;

    auto solution1() -> Answers;
    auto solution2() -> Answers;
    auto solution3() -> Answers;
    auto solution4() -> Answers;

    constexpr int MAX = 4;

    auto selectSolution() -> std::function<Answers()> ;
}

#endif