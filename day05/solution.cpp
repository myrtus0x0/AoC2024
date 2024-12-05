#include "solution.hpp"
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct rule {
    int firstPage;
    int secondPage;
};

int getIndex(const std::vector<int> &section, int value) {
    for (size_t i = 0; i < section.size(); i++) {
        if (section[i] == value) {
            return i;
        }
    }

    return -1;
}

/// XXX: find cleaner way to pass the rules map without using globals
std::unordered_map<int, std::unordered_set<int>> gRules;

bool customCmp(int val1, int val2) {
    // checks whether a rule exists where val1 comes before val2. If this is the
    // case, we return true indicating that val1 should go before val2
    return gRules[val1].find(val2) != gRules[val1].end();
}

std::vector<std::vector<int>>
getValidRows(const std::vector<std::vector<int>> &sections,
             const std::unordered_map<int, std::unordered_set<int>> &rules,
             bool flip) {

    std::vector<std::vector<int>> validRows;
    for (const auto &sect : sections) {
        int rulesToCheck = 0;
        int validRules = 0;

        for (const auto &[first, following] : rules) {
            int firstIndex = getIndex(sect, first);
            for (const auto &second : following) {
                int secondIndex = getIndex(sect, second);
                if (firstIndex == -1 || secondIndex == -1) {
                    continue;
                }

                // we have at least one of the values
                rulesToCheck++;
                // both are inside the section
                if (firstIndex < secondIndex) {
                    validRules++;
                }
            }
        }

        if (rulesToCheck == validRules && !flip) {
            validRows.push_back(sect);
        } else if (rulesToCheck != validRules && flip) {
            validRows.push_back(sect);
        }
    }
    return validRows;
}

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::unordered_map<int, std::unordered_set<int>> rules;
    std::vector<std::vector<int>> sections;

    for (const auto &line : input) {
        if (line.size() == 0) {
            continue;
        }

        size_t delimiterPos = line.find('|');
        // is a rule
        if (delimiterPos != std::string::npos) {
            std::string left = line.substr(0, delimiterPos);
            std::string right = line.substr(delimiterPos + 1);
            rules[stoi(left)].insert(stoi(right));
        } else { // is a page order block
            std::stringstream ss(line);
            std::string number;
            std::vector<int> numbers;

            // for reach line parse the values split by ,
            while (std::getline(ss, number, ',')) {
                numbers.push_back(std::stoi(number));
            }

            if (!numbers.empty()) {
                sections.push_back(numbers);
            }
        }
    }

    int sum = 0;
    // XXX: redundent now. Can just use the same sort logic as part two, but
    // keeping for posterity
    sections = getValidRows(sections, rules, false);
    for (const auto &section : sections) {
        int val = section[floor(section.size() / 2)];
        sum += val;
    }

    return sum;
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    std::vector<std::vector<int>> sections;

    for (const auto &line : input) {
        if (line.size() == 0) {
            continue;
        }

        size_t delimiterPos = line.find('|');
        // is a rule
        if (delimiterPos != std::string::npos) {
            std::string left = line.substr(0, delimiterPos);
            std::string right = line.substr(delimiterPos + 1);
            // instead of using a local var, use global so we can leverage sort
            gRules[stoi(left)].insert(stoi(right));

        } else { // is a page order block
            std::stringstream ss(line);
            std::string number;
            std::vector<int> numbers;

            // for reach line parse the values split by ,
            while (std::getline(ss, number, ',')) {
                numbers.push_back(std::stoi(number));
            }

            if (!numbers.empty()) {
                sections.push_back(numbers);
            }
        }
    }

    int sum = 0;
    // get just the invalid ones
    sections = getValidRows(sections, gRules, true);
    for (auto &section : sections) {
        std::vector<int> unsortedSection = section;
        // can use built in sort to reorder the section for us
        sort(section.begin(), section.end(), customCmp);
        if (unsortedSection != section) {
            int val = section[floor(section.size() / 2)];
            sum += val;
        }
    }

    return sum;
}
