#include "solution.hpp"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::vector<int> list1;
    std::vector<int> list2;

    for (std::string line : input) {
        size_t space = line.find_first_of(" \t");
        list1.push_back(std::stoi(line.substr(0, space)));
        list2.push_back(
            std::stoi(line.substr(line.find_first_not_of(" \t", space))));
    }

    // sort two lists
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    std::vector<int> differences;

    for (auto [l1, l2] : std::views::zip(list1, list2)) {
        int max = l1;
        int min = l2;
        if (l1 < l2) {
            min = l1;
            max = l2;
        }

        differences.push_back(max - min);
    }
    return std::accumulate(differences.begin(), differences.end(), 0);
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    std::vector<int> list1;
    std::vector<int> list2;

    for (std::string line : input) {
        size_t space = line.find_first_of(" \t");
        list1.push_back(std::stoi(line.substr(0, space)));
        list2.push_back(
            std::stoi(line.substr(line.find_first_not_of(" \t", space))));
    }

    int sum = 0;
    for (int v1 : list1) {
        for (int v2 : list2) {
            if (v1 == v2) {
                sum += v1;
            }
        }
    }

    return sum;
}
