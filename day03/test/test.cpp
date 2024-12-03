#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../solution.hpp"
#include "doctest.h"

TEST_CASE("part 1 example") {
    std::vector<std::string> input = {"xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+"
                                      "mul(32,64]then(mul(11,8)mul(8,5))"};

    Solution solution;
    CHECK(solution.solvePart1(input) == 161);
}

TEST_CASE("part 2 example") {
    std::vector<std::string> input = {"xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+"
                                      "mul(32,64](mul(11,8)undo()?mul(8,5))"};

    Solution solution;
    CHECK(solution.solvePart2(input) == 48);
}
