#include "solution.hpp"
#include <cstdint>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

const int BLINKS = 25;
const int SECOND_BLINKS = 75;

uint countDigits(uint64_t n) { return floor(log10(n)) + 1; }

void splitNumber(uint64_t n, uint digits, uint64_t &left, uint64_t &right) {
    int splitPoint = digits / 2;
    uint64_t divisor = 1;
    for (int i = 0; i < digits / 2; i++) {
        divisor *= 10;
    }

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

void enactBlick(std::map<uint64_t, uint64_t> &stones) {
    std::map<uint64_t, uint64_t> copiedStones = stones;

    // iterate over a copy of the map to avoid modifying the map while iterating
    for (const auto &stone : copiedStones) {
        uint64_t val = stone.first;
        uint64_t count = stone.second;

        auto newStones = transform(val);
        stones[val] -= count;

        for (const auto &newStone : newStones) {
            if (stones.find(newStone) == stones.end()) {
                stones[newStone] = 0;
            }

            stones[newStone] += count;
        }
    }
}

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::map<uint64_t, uint64_t> stones;

    std::string newInput = input[0];
    std::stringstream ss(newInput);

    int num;
    while (ss >> num) {
        if (stones.find(num) == stones.end()) {
            stones[num] = 0;
        }

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
    std::map<uint64_t, uint64_t> stones;

    std::string newInput = input[0];
    std::stringstream ss(newInput);

    int num;
    while (ss >> num) {
        if (stones.find(num) == stones.end()) {
            stones[num] = 0;
        }

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
