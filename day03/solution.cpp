#include "solution.hpp"
#include <regex>

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::string toParse = input[0];
    std::regex mulPat(R"(mul\((\d{1,3}),(\d{1,3})\))");

    int sum = 0;

    std::smatch match;
    std::string::const_iterator searchStart(input[0].cbegin());
    while (std::regex_search(searchStart, input[0].cend(), match, mulPat)) {
        searchStart = match.suffix().first;
        sum += (std::stoi(match[1]) * std::stoi(match[2]));
    }

    return sum;
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    std::string toParse = input[0];
    std::regex mulPat(R"(mul\((\d{1,3}),(\d{1,3})\)|(do\(\))|(don't\(\)))");

    int sum = 0;
    bool process = true;

    std::smatch match;
    std::string::const_iterator searchStart(toParse.cbegin());

    while (std::regex_search(searchStart, toParse.cend(), match, mulPat)) {
        searchStart = match.suffix().first;

        // check conditionals, and fallthrough is the math ops
        if (match[0] == "do\()") {
            process = true;
        } else if (match[0] == "don't\()") {
            process = false;
        } else if (process) {
            sum += (std::stoi(match[1]) * std::stoi(match[2]));
        }
    }

    return sum;
}
