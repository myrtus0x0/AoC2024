#include "solution.hpp"
#include <vector>

struct direction {
    int xDelt;
    int yDelt;
};

using grid = std::vector<std::vector<char>>;

const std::vector<direction> directions = {
    {1, 0},   // right
    {0, 1},   // up
    {-1, 0},  // left
    {0, -1},  // down
    {-1, -1}, // diagonal up left
    {-1, 1},  // diagonal up right
    {1, -1},  // diagonal down left
    {1, 1},   // diagonal down right
};

const std::vector<direction> diagonals = {
    {-1, -1}, // diagonal up left
    {-1, 1},  // diagonal up right
    {1, -1},  // diagonal down left
    {1, 1},   // diagonal down right
};

grid parseToGrid(const std::vector<std::string> &input) {
    grid wordGrid;

    for (auto line : input) {
        if (!line.empty()) {
            std::vector<char> row;
            for (char c : line) {
                if (c != '\n' && c != '\r') {
                    row.push_back(c);
                }
            }
            if (!row.empty()) {
                wordGrid.push_back(row);
            }
        }
    }

    return wordGrid;
}

int caclulateMatches(const grid wordGrid, int r, int c) {
    std::string targetStr = "XMAS";
    int targetSize = targetStr.size();
    int total = 0;

    int r_c = r;
    int c_c = c;

    for (auto dir : directions) {
        int matchedChars = 0;

        // reset our start coordinate
        r = r_c;
        c = c_c;
        for (size_t i = 0; i < targetSize; i++) {
            if (wordGrid[r][c] == targetStr[i]) {
                matchedChars++;
            } else { // if we dont match the char, then its a auto fail
                break;
            }

            // success case where we found our word
            if (matchedChars == targetSize) {
                total++;
                break;
            }

            // check min bound
            if ((c + dir.xDelt < 0) || (r + dir.yDelt < 0)) {
                break;
            }

            // check max bound
            if ((c + dir.xDelt >= wordGrid[0].size()) ||
                (r + dir.yDelt >= wordGrid.size())) {
                break;
            }

            // update to next coord
            c += dir.xDelt;
            r += dir.yDelt;
        }
    }

    return total;
}

bool isCross(const grid wordGrid, int r, int c) {
    int diagonalsFound = 0;

    for (auto dia : diagonals) {
        // first char check min bounds
        if ((r - dia.yDelt < 0) || (c - dia.xDelt < 0)) {
            break;
        }

        // first char check inverse min bounds
        if ((r - dia.yDelt >= wordGrid.size()) ||
            (c - dia.xDelt > wordGrid[0].size())) {
            break;
        }

        // third char check min bounds
        if ((r + dia.yDelt < 0) || (c + dia.xDelt < 0)) {
            break;
        }

        // third char check inverse min bounds
        if ((r + dia.yDelt >= wordGrid.size()) ||
            (c + dia.xDelt > wordGrid[0].size())) {
            break;
        }

        // at this point we are guaranteed our bounds are going to be valid
        if (std::string{wordGrid[r - dia.yDelt][c - dia.xDelt], wordGrid[r][c],
                        wordGrid[r + dia.yDelt][c + dia.xDelt]} == "MAS") {
            diagonalsFound++;
        }
    }

    if (diagonalsFound == 2) {
        return true;
    }

    return false;
}

int Solution::solvePart1(const std::vector<std::string> &input) {
    grid wordGrid = parseToGrid(input);

    int sum = 0;
    // iterate over every starting point in the grid
    for (size_t r = 0; r < wordGrid.size(); r++) {
        for (size_t c = 0; c < wordGrid[0].size(); c++) {
            // slight optimization
            if (wordGrid[r][c] == 'X') {
                sum += caclulateMatches(wordGrid, r, c);
            }
        }
    }

    return sum;
}

int Solution::solvePart2(const std::vector<std::string> &input) {
    grid wordGrid = parseToGrid(input);
    int sum = 0;
    for (size_t r = 0; r < wordGrid.size(); r++) {
        for (size_t c = 0; c < wordGrid[0].size(); c++) {
            // slight optimization
            if (wordGrid[r][c] == 'A') {
                if (isCross(wordGrid, r, c)) {
                    sum++;
                }
            }
        }
    }

    return sum;
}
