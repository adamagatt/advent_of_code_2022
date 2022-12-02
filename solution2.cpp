#include "solutions.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <unordered_map>

#include "utils/read_utils.h"

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

auto matchupResult(Shape theirs, Shape mine) -> Result {
    return (mine == theirs)           ? Result::DRAW
         : (mine == beats.at(theirs)) ? Result::WIN
         :                              Result::LOSE;
}

const std::unordered_map<Result, int> scoreForResult {
    {Result::WIN,  6},
    {Result::DRAW, 3},
    {Result::LOSE, 0}
};

auto scoreShapes(const std::pair<Shape, Shape>& shapes) -> int {
    const auto& [theirs, mine] = shapes;
    return scoreForResult.at(matchupResult(theirs, mine)) + static_cast<int>(mine);
}

auto shapeToGetResult(Shape theirs, Result result) -> Shape {
    return (result == Result::DRAW) ? theirs
         : (result == Result::WIN)  ? beats.at(theirs)
         :                            beats.at(beats.at(theirs)); // Lol ugly hack
}

template <typename T, typename U>
auto parseChars(const std::unordered_map<char, T>& firstMap, const std::unordered_map<char, U>& secondMap) {
    return [&firstMap, &secondMap](const std::string& input) -> std::pair<T, U> {
        return { firstMap.at(input.at(0)), secondMap.at(input.at(2)) };
    };
}

auto Solutions::Solution2() -> Answers {

    auto inputs = ReadUtils::lines("inputs/input2.txt");

    auto scoresPartA = inputs
        | std::views::transform(parseChars(charToShape, charToShape))
        | std::views::transform(scoreShapes);

    int answerA = std::accumulate(scoresPartA.begin(), scoresPartA.end(), 0);

    auto scoresPartB = inputs
        | std::views::transform(parseChars(charToShape, charToResult))
        // We want to convert a (Shape, Result) pair into a (Shape, Shape) pair
        // that achieves that Result
        | std::views::transform([](const std::pair<Shape, Result>& parsed) {
            const auto& [theirs, result] = parsed;
            return std::pair{theirs, shapeToGetResult(theirs, result)};
        })
        | std::views::transform(scoreShapes);

    int answerB = std::accumulate(scoresPartB.begin(), scoresPartB.end(), 0);

    return { answerA, answerB };
}