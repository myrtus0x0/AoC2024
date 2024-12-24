#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../solution.hpp"
#include "doctest.h"

TEST_CASE("part 1 example") {
    std::vector<std::string> input = {
        "89010123", "78121874", "87430965", "96549874",
        "45678903", "32019012", "01329801", "10456732",
    };

    Solution solution;
    CHECK(solution.solvePart1(input) == 36);
}

TEST_CASE("part 2 example") {
    std::vector<std::string> input = {
        "89010123", "78121874", "87430965", "96549874",
        "45678903", "32019012", "01329801", "10456732",
    };

    Solution solution;
    CHECK(solution.solvePart2(input) == 81);
}
