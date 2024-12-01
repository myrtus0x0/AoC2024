#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../solution.hpp"
#include "doctest.h"

TEST_CASE("part 1 example") {
    std::vector<std::string> input = {
        "3   4", "4   3", "2   5", "1   3", "3   9", "3   3",
    };

    Solution solution;
    CHECK(solution.solvePart1(input) == 11);
}

TEST_CASE("part 2 example") {
    std::vector<std::string> input = {
        "3   4", "4   3", "2   5", "1   3", "3   9", "3   3",
    };

    Solution solution;
    CHECK(solution.solvePart2(input) == 31);
}
