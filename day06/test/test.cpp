#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../solution.hpp"
#include "doctest.h"

TEST_CASE("part 1 example") {
    std::vector<std::string> input = {
        "....#.....", ".........#", "..........", "..#.......", ".......#..",
        "..........", ".#..^.....", "........#.", "#.........", "......#...",
    };

    Solution solution;
    CHECK(solution.solvePart1(input) == 41);
}

TEST_CASE("part 2 example") {
    std::vector<std::string> input = {
        "....#.....", ".........#", "..........", "..#.......", ".......#..",
        "..........", ".#..^.....", "........#.", "#.........", "......#...",

    };

    Solution solution;
    CHECK(solution.solvePart2(input) == 6);
}
