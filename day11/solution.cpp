#include "solution.hpp"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

const int BLINKS = 25;
const int SECOND_BLINKS = 75;

uint countDigits(uint64_t n) { return floor(log10(n)) + 1; }

void splitNumber(uint64_t n, uint digits, uint64_t &left, uint64_t &right) {
    uint64_t divisor = pow(10, digits / 2);
    right = n % divisor;
    left = n / divisor;
}

std::vector<uint64_t> transform(uint64_t stoneNumber) {
    if (stoneNumber == 0) {
        return {1};

    } else {
        uint64_t digits = countDigits(stoneNumber);
        if (digits % 2 == 0) {
            uint64_t left, right;
            splitNumber(stoneNumber, digits, left, right);
            return {left, right};

        } else {
            return {uint64_t(stoneNumber * 2024)};
        }
    }
}

void enactBlick(std::unordered_map<uint64_t, size_t> &stones) {
    std::unordered_map<uint64_t, size_t> newStones;
    for (const auto &stone : stones) {
        uint64_t val = stone.first;
        uint64_t count = stone.second;

        auto transformedStones = transform(val);
        for (const auto &newStone : transformedStones) {
            newStones[newStone] += count;
        }
    }

    // basically everything in the old list can be ignored as the rules
    // guarantee every stone is modified
    stones = std::move(newStones);
}

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::unordered_map<uint64_t, size_t> stones;

    std::string newInput = input[0];
    std::stringstream ss(newInput);

    int num;
    while (ss >> num) {
        stones[num]++;
    }

    for (size_t b = 0; b < BLINKS; b++) {
        enactBlick(stones);
    }

    uint64_t sum = 0;
    for (const auto &pair : stones) {
        sum += pair.second;
    }

    return sum;
}

uint64_t Solution::solvePart2(const std::vector<std::string> &input) {
    std::unordered_map<uint64_t, size_t> stones;

    std::string newInput = input[0];
    std::stringstream ss(newInput);

    int num;
    while (ss >> num) {
        stones[num]++;
    }

    for (size_t b = 0; b < SECOND_BLINKS; b++) {
        enactBlick(stones);
    }

    uint64_t sum = 0;
    for (const auto &pair : stones) {
        sum += pair.second;
    }

    return sum;
}
