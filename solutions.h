#ifndef __SOLUTIONS_H
#define __SOLUTIONS_H

#include <utility>

namespace Solutions {
    using Answers = std::pair<int, int>;

    constexpr int MAX = 3;

    auto Solution1() -> Answers;
    auto Solution2() -> Answers;
    auto Solution3() -> Answers;
}

#endif