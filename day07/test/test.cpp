#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../solution.hpp"
#include "doctest.h"

TEST_CASE("part 1 example") {
    std::vector<std::string> input = {
        "190: 10 19",   "3267: 81 40 27",   "83: 17 5",
        "156: 15 6",    "7290: 6 8 6 15",   "161011: 16 10 13",
        "192: 17 8 14", "21037: 9 7 18 13", "292: 11 6 16 20",
    };

    Solution solution;
    CHECK(solution.solvePart1(input) == 3749);
}

TEST_CASE("part 2 example") {
    std::vector<std::string> input = {
        "190: 10 19",   "3267: 81 40 27",   "83: 17 5",
        "156: 15 6",    "7290: 6 8 6 15",   "161011: 16 10 13",
        "192: 17 8 14", "21037: 9 7 18 13", "292: 11 6 16 20",
    };

    Solution solution;
    CHECK(solution.solvePart2(input) == 0);
}
