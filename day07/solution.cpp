#include "solution.hpp"
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

void generateAlgo(const std::vector<char> &ops, size_t nOperators,
                  size_t nNumbers, std::vector<std::string> &equations,
                  std::string equation = "") {
    // we can filter this down to just accept equations that are N-1 length, but lazy
    if (nNumbers == 0) {
        equations.push_back(equation);
        return;
    }

    for (int i = 0; i < nOperators; i++) {
        generateAlgo(ops, nOperators, nNumbers - 1, equations,
                     equation + ops[i]);
    }
}

std::vector<std::string> genCombos(const std::vector<char> &operators,
                                   size_t n) {
    std::vector<std::string> result;
    generateAlgo(operators, operators.size(), n, result);
    return result;
}

bool checkCombos(const std::vector<int64_t> &operators, int64_t target) {
    int64_t tempTotal;
    std::vector<char> operands = {'*', '+'};
    auto combos = genCombos(operands, operators.size());
    for (auto combo : combos) {
        // we only care about algos that are N-1 size of input list of numbers
        if (combo.size() < operators.size() - 1) {
            continue;
        }

        tempTotal = operators[0];
        for (size_t i = 1; i < combo.size(); i++) {
            char operand = combo[i-1];
            if (operand == '*') {
                tempTotal *= operators[i];
            } else if (operand == '+') {
                tempTotal += operators[i];
            }
        }

        if (tempTotal == target) {
            return true;
        }
    }

    return false;
}

int64_t Solution::solvePart1(const std::vector<std::string> &input) {
    int64_t sum = 0;

    for (auto line : input) {
        std::istringstream iss(line);
        std::string targetStr;
        std::getline(iss, targetStr, ':');
        int64_t target = std::stoll(targetStr);

        std::vector<int64_t> numbers;
        int64_t num;
        while (iss >> num) {
            numbers.push_back(num);
        }

        if (checkCombos(numbers, target)) {
            sum += target;
        }
    }
    
    return sum;
}

int64_t Solution::solvePart2(const std::vector<std::string> &input) {
    // TODO: implement me
    return 0;
}
