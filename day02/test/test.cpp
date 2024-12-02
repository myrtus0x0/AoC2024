#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../solution.hpp"
#include "doctest.h"

TEST_CASE("part 1 example") {
    std::vector<std::string> input = {
        "7 6 4 2 1", "1 2 7 8 9", "9 7 6 2 1",
        "1 3 2 4 5", "8 6 4 4 1", "1 3 6 7 9",
    };

    Solution solution;
    CHECK(solution.solvePart1(input) == 2);
}

TEST_CASE("part 2 example") {
    std::vector<std::string> input = {
        "7 6 4 2 1", "1 2 7 8 9", "9 7 6 2 1",
        "1 3 2 4 5", "8 6 4 4 1", "1 3 6 7 9",
    };

    Solution solution;
    CHECK(solution.solvePart2(input) == 4);
}
