#pragma once
#include <set>
#include <string>
#include <vector>

class Solution {
  public:
    int solvePart1(const std::vector<std::string> &input);
    int solvePart2(const std::vector<std::string> &input);
};

struct direction {
    int cDelt;
    int rDelt;
};

struct location {
    int row;
    int col;
    char value;
    int dir;

    bool operator<(const location &other) const {
        if (row != other.row)
            return row < other.row;
        if (col != other.col)
            return col < other.col;
        return dir < other.dir;
    }
};

struct coord {
    int r;
    int c;

    bool operator<(const coord& other) const {
        if (c != other.c) return c < other.c;
        return r < other.r;
    }
};

class guardedMap {
  private:
    int iDir = 0;
    location guardLocation;

  public:
    std::set<location> visited;
    std::vector<std::vector<location>> map;
    bool infiniteLoopDetected = false;

    bool checkBeenHere();
    void moveGuard();
    bool isGuardInMap();
    void updatePath();
    void initGuardLocation();
    void printMap();
    size_t getPath();
    guardedMap(const std::vector<std::vector<location>> &initialMap =
                   std::vector<std::vector<location>>());
};
