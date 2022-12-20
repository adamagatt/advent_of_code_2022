#include "solutions.h"
#include "solution2.h"

#include "../utils/read.h"

#include <algorithm>
#include <execution>
#include <numeric>

namespace rv = std::views;

auto Solutions::solution2() -> Answers {
    const auto& par_vec = std::execution::par_unseq;

    auto inputs = Utils::readLines("inputs/input2.txt");

    auto scoresPartA = inputs
        | rv::transform(parseChars(charToShape, charToShape))
        | rv::transform([](const std::pair<Shape, Shape>& shapes) {
            const auto& [theirs, mine] = shapes;
            return std::pair{matchupResult(theirs, mine), mine};
        })
        | rv::transform(scoreRound);

    int answerA = std::reduce(par_vec, scoresPartA.begin(), scoresPartA.end());

    auto scoresPartB = inputs
        | rv::transform(parseChars(charToShape, charToResult))
        | rv::transform([](const std::pair<Shape, Result>& parsed) {
            const auto& [theirs, result] = parsed;
            return std::pair{result, shapeToGetResult(theirs, result)};
        })
        | rv::transform(scoreRound);

    int answerB = std::reduce(par_vec, scoresPartB.begin(), scoresPartB.end());

    return { std::to_string(answerA), std::to_string(answerB) };
}

auto matchupResult(const Shape& theirs, const Shape& mine) -> Result {
    Result result = (mine == theirs)           ? Result::DRAW
                  : (mine == beats.at(theirs)) ? Result::WIN
                  :                              Result::LOSE;
    
    return result;
}

auto scoreRound(const std::pair<Result, Shape>& factors) -> int {
    const auto& [result, myShape] = factors;
    return scoreForResult.at(result) + static_cast<int>(myShape);
}

auto shapeToGetResult(Shape theirs, Result result) -> Shape {
    return (result == Result::DRAW) ? theirs
         : (result == Result::WIN)  ? beats.at(theirs)
         : /* Losing shape */         beats.at(beats.at(theirs));
}