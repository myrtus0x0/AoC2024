#include "solution.hpp"
#include <iostream>
#include <ostream>

const std::vector<direction> directions = {
    {0, -1}, // up
    {1, 0},  // right
    {0, 1},  // down
    {-1, 0}, // left

};

void guardedMap::printMap() {
    for (const auto &row : map) {
        for (const auto &mem : row) {
            std::cout << mem.value;
        }
        std::cout << std::endl;
    }
}

size_t guardedMap::getPath() {
    size_t total = 0;

    for (const auto &row : map) {
        for (const auto &mem : row) {
            if (mem.value == 'X' || mem.value == '^') {
                total++;
            }
        }
    }

    return total;
}

location guardedMap::getGuardLocation() {
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[r].size(); c++) {
            if (map[r][c].value == '^') {
                return {r, c, '^'};
            }
        }
    }

    return {-1, -1, '.'};
}

void guardedMap::moveGuard() {
    location guardLocation = getGuardLocation();
    if (guardLocation.row == -1 || guardLocation.col == -1) {
        return;
    }

    guardLocation.dir = iDir % 4;
    if (!visited.insert(guardLocation).second) {
        // not worth processing as inf loop has been detected
        // std::cout << "inf loop detected" << std::endl;
        infiniteLoopDetected = true;
        return;
    }

    int newR = guardLocation.row + directions[iDir % 4].rDelt;
    int newC = guardLocation.col + directions[iDir % 4].cDelt;
    // if we move out of bounds, then guard has escaped and we can return
    if (newR >= map.size() || newC >= map[0].size() || newR < 0 || newC < 0) {
        return;
    }

    location potentialNextSpot = {newR, newC, map[newR][newC].value};

    if (potentialNextSpot.value == '.' || potentialNextSpot.value == 'X') {
        // Move guard forward
        map[newR][newC].value = '^';
        map[guardLocation.row][guardLocation.col].value = 'X';

    } else if (potentialNextSpot.value == '#') {
        iDir++;
    }

    moveGuard();
}

guardedMap::guardedMap(const std::vector<std::vector<location>> &initialMap)
    : map(initialMap) {}

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::vector<std::vector<location>> map;
    location guardStart;

    for (int r = 0; r < input.size(); r++) {
        std::vector<location> row;
        for (int c = 0; c < input[r].size(); c++) {
            row.push_back({r, c, input[r][c]});
        }
        map.push_back(row);
    }

    guardedMap myMap(map);
    // traverse!!!!
    myMap.moveGuard();
    return myMap.getPath();
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    std::vector<std::vector<location>> map;
    location guardStart;
    int blockers = 0;

    for (int r = 0; r < input.size(); r++) {
        std::vector<location> row;
        for (int c = 0; c < input[r].size(); c++) {
            row.push_back({r, c, input[r][c]});
        }
        map.push_back(row);
    }

    guardedMap solvedMap(map);
    // calculate the path moved as those are the only locations we need to test
    solvedMap.moveGuard();

    std::set<coord> points;

    for (auto location : solvedMap.visited) {
        guardedMap newMap(map);
        if (points.find({location.row, location.col}) != points.end()) {
            continue;
        }

        newMap.map[location.row][location.col].value = '#';
        newMap.moveGuard();
        if (newMap.infiniteLoopDetected) {
            blockers++;
        }

        points.insert({location.row, location.col});
    }

    return blockers;
}
