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

void guardedMap::initGuardLocation() {
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[r].size(); c++) {
            if (map[r][c].value == '^') {
                guardLocation.row = r;
                guardLocation.col = c;
                guardLocation.dir = iDir % 4;
            }
        }
    }
}

void guardedMap::moveGuard() {
    while (true) {
        if (!visited.insert(guardLocation).second) {
            // not worth processing as inf loop has been detected
            infiniteLoopDetected = true;
            break;
        }

        int newR = guardLocation.row + directions[iDir % 4].rDelt;
        int newC = guardLocation.col + directions[iDir % 4].cDelt;
        // if we move out of bounds, then guard has escaped and we can return
        if (newR >= map.size() || newC >= map[newR].size() || newR < 0 ||
            newC < 0) {
            break;
        }

        location potentialNextSpot = {newR, newC, map[newR][newC].value};

        if (potentialNextSpot.value == '.' || potentialNextSpot.value == 'X') {
            // Move guard forward
            map[newR][newC].value = '^';
            map[guardLocation.row][guardLocation.col].value = 'X';
            guardLocation.row = newR;
            guardLocation.col = newC;

        } else if (potentialNextSpot.value == '#') {
            iDir++;
            guardLocation.dir = iDir % 4;
        }
    }

    return;
}

guardedMap::guardedMap(const std::vector<std::vector<location>> &initialMap)
    : map(initialMap) {}

int Solution::solvePart1(const std::vector<std::string> &input) {
    std::vector<std::vector<location>> map;
    location guardLoc;

    for (int r = 0; r < input.size(); r++) {
        std::vector<location> row;
        for (int c = 0; c < input[r].size(); c++) {
            row.push_back({r, c, input[r][c]});
            if (input[r][c] == '^') {
                guardLoc = {r, c};
            }
        }
        map.push_back(row);
    }

    guardedMap myMap(map);
    // traverse!!!!
    myMap.guardLocation.row = guardLoc.row;
    myMap.guardLocation.col = guardLoc.col;
    myMap.moveGuard();
    return myMap.getPath();
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    std::vector<std::vector<location>> map;
    int blockers = 0;
    location guardLoc;

    // parse the map
    for (int r = 0; r < input.size(); r++) {
        std::vector<location> row;
        for (int c = 0; c < input[r].size(); c++) {
            row.push_back({r, c, input[r][c]});
            if (input[r][c] == '^') {
                guardLoc = {r, c};
            }
        }
        map.push_back(row);
    }

    guardedMap solvedMap(map);
    // calculate the path moved as those are the only locations we need to test
    solvedMap.guardLocation.row = guardLoc.row;
    solvedMap.guardLocation.col = guardLoc.col;
    solvedMap.guardLocation.dir = 0;
    solvedMap.moveGuard();

    std::set<coord> points;

    for (const auto &location : solvedMap.visited) {
        guardedMap newMap(map);
        // is the guard location so we dont count it
        if (guardLoc.col == location.col && guardLoc.row == location.row) {
            continue;
        }

        // if we already visited the point, then ignore
        if (points.find({location.row, location.col}) != points.end()) {
            continue;
        }

        newMap.map[location.row][location.col].value = '#';
        newMap.guardLocation.row = guardLoc.row;
        newMap.guardLocation.col = guardLoc.col;
        newMap.guardLocation.dir = 0;
        newMap.moveGuard();
        if (newMap.infiniteLoopDetected) {
            blockers++;
        }

        points.insert({location.row, location.col});
    }

    return blockers;
}
