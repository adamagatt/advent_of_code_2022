#include "solutions.h"

#include "../utils/read.h"

#include <array>
#include <deque>
#include <iterator>
#include <utility>

using Stack = std::deque<char>;
using Stacks = std::array<Stack, 9>;

struct Instruction {
    int amount;
    int source;
    int dest;
};

auto parseInput(std::vector<std::string> lines) -> std::pair<Stacks, std::vector<Instruction>> {
    Stacks initialStacks;
    std::vector<Instruction> instructions;

    auto curLine = lines.cbegin();
    // while (curLine->con)

 
    return {initialStacks, instructions};
}

auto executeInstruction(Stacks& stacks, const Instruction& instruction) {
    Stack& sourceStack = stacks[instruction.source - 1];
    Stack& destStack = stacks[instruction.dest - 1];

    destStack.insert(
        destStack.cend(),
        std::move_iterator(sourceStack.rbegin()),
        std::move_iterator(std::next(sourceStack.rbegin(), instruction.amount))
    );
}

auto Solutions::solution5() -> Answers {
    auto [stacks, instructions] = parseInput(Utils::readLines("inputs/input5.txt"));

    for (const Instruction& instruction : instructions) {
        executeInstruction(stacks, instruction);
    }

    return {"", ""};
}