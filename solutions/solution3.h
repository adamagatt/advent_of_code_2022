#ifndef __SOLUTION3_H_
#define __SOLUTION3_H_

#include <string>

auto priority(char c) -> int;

auto doubledItem(const std::string& line) -> char;

auto presentInThreePacks(
    const std::string& elf1,
    const std::string& elf2,
    const std::string& elf3
) -> char;

#endif