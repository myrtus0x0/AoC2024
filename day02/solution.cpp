#include "solution.hpp"
#include <sstream>
#include <vector>

struct report {
    std::vector<int> levels;
};

bool isSafe(const report currentReport) {
    bool increasing = currentReport.levels[1] > currentReport.levels[0];

    for (size_t i = 1; i < currentReport.levels.size(); i++) {
        int diff = currentReport.levels[i] - currentReport.levels[i - 1];
        int absDiff = std::abs(diff);
        // check jump amount
        if (absDiff < 1 || absDiff > 3) {
            return false;
        }

        // check if break increasing rule
        if (increasing && diff <= 0) {
            return false;
        }

        // check if break decreasing rule
        if (!increasing && diff >= 0) {
            return false;
        }
    }

    return true;
}

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::vector<report> reports;

    for (auto line : input) {
        report currentReport;
        std::istringstream lineStream(line);
        int number;
        // read ints from whitespace delimited line
        while (lineStream >> number) {
            currentReport.levels.push_back(number);
        }

        if (!currentReport.levels.empty()) {
            reports.push_back(currentReport);
        }
    }

    int safeReports = 0;

    for (auto report : reports) {
        if (isSafe(report)) {
            safeReports += 1;
        }
    }

    return safeReports;
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    std::vector<report> reports;

    for (auto line : input) {
        report currentReport;
        std::istringstream lineStream(line);
        int number;

        while (lineStream >> number) {
            currentReport.levels.push_back(number);
        }

        if (!currentReport.levels.empty()) {
            reports.push_back(currentReport);
        }
    }

    int safeReports = 0;

    for (auto currentReport : reports) {
        for (size_t i = 0; i < currentReport.levels.size(); i++) {
            report newReport = currentReport;
            // NewReport now contains a copy of the report with a specific level
            // removed. 
            //
            // XXX: hack of just removing all entries one by one and
            // seeing if it results in same. Change this logic to be more
            // efficient, so we dont need to make potentially 5 copies
            newReport.levels.erase(newReport.levels.begin() + i);
            if (isSafe(newReport)) {
                // if we see its safe, we stop processing and go to next report
                safeReports += 1;
                break;
            }
        }
    }

    return safeReports;
}
