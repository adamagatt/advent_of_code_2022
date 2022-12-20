#ifndef __SOLUTION2_H_
#define __SOLUTION2_H_

#include <unordered_map>
#include <utility>

/// Shapes include the score gained for us throwing them
enum class Shape : int { ROCK = 1, PAPER = 2, SCISSORS = 3 };

enum class Result {WIN, LOSE, DRAW};

const std::unordered_map<char, Shape> charToShape {
    { 'A', Shape::ROCK },
    { 'B', Shape::PAPER },
    { 'C', Shape::SCISSORS },
    { 'X', Shape::ROCK },
    { 'Y', Shape::PAPER },
    { 'Z', Shape::SCISSORS }
};

const std::unordered_map<char, Result> charToResult {
    { 'X', Result::LOSE },
    { 'Y', Result::DRAW },
    { 'Z', Result::WIN }
};

/// Pairs of shapes where the second beats the first
const std::unordered_map<Shape, Shape> beats {
    {Shape::ROCK, Shape::PAPER},
    {Shape::PAPER, Shape::SCISSORS},
    {Shape::SCISSORS, Shape::ROCK}
};

const std::unordered_map<Result, int> scoreForResult {
    {Result::WIN,  6},
    {Result::DRAW, 3},
    {Result::LOSE, 0}
};

auto matchupResult(const Shape& theirs, const Shape& mine) -> Result;

auto scoreRound(const std::pair<Result, Shape>& factors) -> int;

auto shapeToGetResult(Shape theirs, Result result) -> Shape;

/**
 * Creates and returns a mapping function that will accept a line of two characters
 * and convert them into a pair of enums. This is templated to allow us to convert
 * each line to a (Shape, Shape) pair for Part A and a (Shape, Result) pair for
 * Part B.
 * 
 * @tparam T The type that the first map will convert characters to
 * @tparam U The type that the second map will convert characters to
 * @param firstMap A map for transforming char -> T
 * @param secondMap A map for transformation char -> U
 * @return auto A mapping function (char, char) -> (T, U) that can be supplied to
 * std::transform to convert an input line into a pair of types determined by the
 * supplied maps
 */
template <typename T, typename U>
auto parseChars(
    const std::unordered_map<char, T>& firstMap,
    const std::unordered_map<char, U>& secondMap
) {
    return [&firstMap, &secondMap](const std::string& input) -> std::pair<T, U> {
        return { firstMap.at(input.at(0)), secondMap.at(input.at(2)) };
    };
}

#endif