#include "solution.hpp"
#include <string>
#include <vector>

struct coordinate {
    size_t row;
    size_t column;
    u_int32_t value;
};

struct trailMap {
    std::vector<std::vector<coordinate>> rawMap;
    std::vector<coordinate> startLocations;
    size_t numValidPaths;
};

struct direction {
    int rDelta;
    int cDelta;
};

std::vector<direction> directions{
    {1, 0},  // down
    {0, 1},  // right
    {-1, 0}, // up
    {0, -1}  // left
};

void traverse(trailMap &tMap, const coordinate &currentLocation,
              std::vector<std::vector<bool>> &visited) {
    visited[currentLocation.row][currentLocation.column] = true;
    if (currentLocation.value == '9') {
        tMap.numValidPaths++;
        return;
    }

    for (const auto &dir : directions) {
        size_t newR = currentLocation.row + dir.rDelta;
        size_t newC = currentLocation.column + dir.cDelta;

        // handle out of bounds issues
        if (newR >= tMap.rawMap.size() || newC >= tMap.rawMap[newR].size()) {
            continue;
        }

        coordinate newLocation = tMap.rawMap[newR][newC];
        if (!visited[newR][newC] &&
            newLocation.value == currentLocation.value + 1) {
            traverse(tMap, newLocation, visited);
        }
    }

    visited[currentLocation.row][currentLocation.column] = false;
    return;
}

void traverse(trailMap &tMap, const coordinate &currentLocation) {
    if (currentLocation.value == '9') {
        tMap.numValidPaths++;
        return;
    }

    for (auto dir : directions) {
        size_t newR = currentLocation.row + dir.rDelta;
        size_t newC = currentLocation.column + dir.cDelta;

        // handle out of bounds issues
        if (newR >= tMap.rawMap.size() || newC >= tMap.rawMap[newR].size()) {
            continue;
        }

        coordinate newLocation = tMap.rawMap[newR][newC];
        if (newLocation.value == currentLocation.value + 1) {
            traverse(tMap, newLocation);
        }
    }

    return;
}

int Solution::solvePart1(const std::vector<std::string> &input) {
    trailMap tMap;
    tMap.numValidPaths = 0;
    for (size_t r = 0; r < input.size(); r++) {
        std::vector<coordinate> currentRow;
        for (size_t c = 0; c < input[r].size(); c++) {
            coordinate currentLocation = coordinate(r, c, input[r][c]);
            currentRow.push_back(currentLocation);
            if (input[r][c] == '0') {
                tMap.startLocations.push_back(currentLocation);
            }
        }

        tMap.rawMap.push_back(currentRow);
    }

    int sum = 0;
    std::vector<std::vector<bool>> visited(
        tMap.rawMap.size(),
        std::vector<bool>(tMap.rawMap[0].size(), false));

    for (auto startLoc : tMap.startLocations) {
        tMap.numValidPaths = 0;
        traverse(tMap, startLoc, visited);

        // reset the state of visited
        for (auto &row: visited) {
            for (auto col: row) {
                col = false;
            }
        }
        sum += tMap.numValidPaths;
    }

    return sum;
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    trailMap tMap;
    tMap.numValidPaths = 0;
    for (size_t r = 0; r < input.size(); r++) {
        std::vector<coordinate> currentRow;
        for (size_t c = 0; c < input[r].size(); c++) {
            coordinate currentLocation = coordinate(r, c, input[r][c]);
            currentRow.push_back(currentLocation);
            if (input[r][c] == '0') {
                tMap.startLocations.push_back(currentLocation);
            }
        }

        tMap.rawMap.push_back(currentRow);
    }
    int sum = 0;
    for (auto startLoc : tMap.startLocations) {
        tMap.numValidPaths = 0;
        traverse(tMap, startLoc);
        sum += tMap.numValidPaths;
    }

    return sum;
}
