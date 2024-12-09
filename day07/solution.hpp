#pragma once
#include <string>
#include <vector>

bool checkCombos(const std::vector<int64_t>& nums, int64_t target, size_t i, int64_t current);

class Solution {
public:
    int64_t solvePart1(const std::vector<std::string>& input);
    int64_t solvePart2(const std::vector<std::string>& input);
};
