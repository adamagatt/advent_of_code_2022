#ifndef __FUNCTIONAL_H
#define __FUNCTIONAL_H

#include <functional>
#include <unordered_set>

namespace Utils {

    // Lambda over function definition to allow for complex auto-deduced return type
    auto inSet = [](const std::unordered_set<char>& set){
        return std::bind_front(&std::unordered_set<char>::contains, set);
    };

    auto notInSet = [](const std::unordered_set<char>& set){
        return std::not_fn(inSet(set));
    };
}

#endif