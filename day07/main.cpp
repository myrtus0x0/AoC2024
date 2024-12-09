#include "solution.hpp"
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename T> struct timer;

template <typename R, typename C, typename... Args>
struct timer<R (C::*)(Args...)> {
    using fn = R (C::*)(Args...);

    static R time(fn func, C *obj, Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        R retval = (obj->*func)(args...);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << std::format("Func took {:.2f} milliseconds",
                                 static_cast<float>(duration.count()) / 1000)
                  << std::endl;

        return retval;
    }
};

std::vector<std::string> readInput(const std::string &filename) {
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

    auto res1 = timer<decltype(&Solution::solvePart1)>::time(
        &Solution::solvePart1, &solution, input);
    std::cout << "Part 1: " << res1 << std::endl;

    auto res2 = timer<decltype(&Solution::solvePart2)>::time(
        &Solution::solvePart2, &solution, input);
    std::cout << "Part 2: " << res2 << std::endl;

    return 0;
}
