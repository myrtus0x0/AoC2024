#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "solution.hpp"

std::vector<std::string> readInput(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    return lines;
}

int main() {
    auto input = readInput("input.txt");
    Solution solution;
    
    std::cout << "Part 1: " << solution.solvePart1(input) << std::endl;
    std::cout << "Part 2: " << solution.solvePart2(input) << std::endl;
    
    return 0;
}
