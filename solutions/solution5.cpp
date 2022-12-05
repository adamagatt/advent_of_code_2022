#include "solutions.h"

#include "../utils/read.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <deque>
#include <sstream>
#include <utility>

using Stack = std::deque<char>;
using Stacks = std::array<Stack, 9>;

struct Instruction {
    int amount;
    int source;
    int dest;
};

auto nextInteger(std::stringstream& ss) -> int {
    int i;

    while (!std::isdigit(ss.peek())) {
        ss.ignore(1);
    }
    ss >> i;
    return i;
}

auto parseInput(std::vector<std::string> lines) -> std::pair<Stacks, std::vector<Instruction>> {
    Stacks initialStacks;
    std::vector<Instruction> instructions;

    auto curLine = lines.cbegin();
    // Initial stack info has at least one '[' per line
    for ( ; curLine->find('[') != std::string::npos; ++curLine) {
        for (int i = 0; i < 9; i++) {
            if (char foundChar = curLine->at(i*4+1); foundChar != ' ') {
                // push_front as stacks are built top-down
                initialStacks[i].push_front(foundChar);
            }
        }
    }

    // Skip the next two lines to get to instructions
    std::advance(curLine, 2);

    // Read instructions from here
    for ( ; curLine != lines.cend(); ++curLine) {
        int amount{}, source{}, dest{};
        std::stringstream ss(*curLine);
        amount = nextInteger(ss);
        source = nextInteger(ss);
        dest = nextInteger(ss);

        instructions.emplace_back(amount, source, dest);
    }

    return {initialStacks, instructions};
}

auto executeInstruction(Stacks& stacks, const Instruction& instruction, bool reverseOrder) {
    Stack& sourceStack = stacks[instruction.source - 1];
    Stack& destStack = stacks[instruction.dest - 1];

    if (reverseOrder) {
        // Reverse source iterators to copy elements across in reverse order.
        // Simulates the reversing effect of moving crates one-by-one.
        destStack.insert(
            destStack.cend(),
            sourceStack.crbegin(),
            std::next(sourceStack.crbegin(), instruction.amount)
        );
    } else {
        // Wish I could switch on only the iterators instead of the entire
        // algorithm call but I'm not sure I can store an std::iterator and
        // std::reverse_iterator in the same type
        destStack.insert(
            destStack.cend(),
            std::prev(sourceStack.cend(), instruction.amount),
            sourceStack.cend()
        );
    }

    // Would use deque::erase but apparently doesn't support reverse iterators
    for (int i = 0; i < instruction.amount; ++i) {
        sourceStack.pop_back();
    }
}

auto solutionAnswer(const Stacks& stacks) -> std::string {
    std::string answer{};
    for (const Stack& stack : stacks) {
        answer.push_back(stack.back());
    }
    return answer;
}

auto Solutions::solution5() -> Answers {
    auto [stacksPartA, instructions] = parseInput(Utils::readLines("inputs/input5.txt"));
    // Preserve original ordering for solving part B
    Stacks stacksPartB = stacksPartA;

    // Run through instruction list for both parts of problem
    for (const Instruction& instruction : instructions) {
        executeInstruction(stacksPartA, instruction, true);
        executeInstruction(stacksPartB, instruction, false);
    }

    return {solutionAnswer(stacksPartA), solutionAnswer(stacksPartB)};
}