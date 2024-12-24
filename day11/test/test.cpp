#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../solution.hpp"

TEST_CASE("part 1 example") {
    std::vector<std::string> input = {
        "125 17",
    };

    Solution solution;
    CHECK(solution.solvePart1(input) == 55312);
}

TEST_CASE("part 2 example") {
    std::vector<std::string> input = {
        "125 17",
    };

    Solution solution;
    CHECK(solution.solvePart2(input) == 55312);
}
