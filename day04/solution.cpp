#include "solution.hpp"
#include <vector>

struct direction {
    int cDelt;
    int rDelt;
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

int caclulateMatches(const grid &wordGrid, int r, int c) {
    std::string targetStr = "XMAS";
    int targetSize = targetStr.size();

    int columnSize = wordGrid[0].size();
    int rowSize = wordGrid.size();

    int total = 0;

    int r_c = r;
    int c_c = c;

    for (auto dir : directions) {
        int matchedChars = 0;
        // reset our start coordinate
        r = r_c;
        c = c_c;

        // if last char in the string direction is out of bounds we know its
        // wrong
        if ((r + (3 * dir.rDelt) >= rowSize) || (r + (3 * dir.rDelt) < 0)) {
            continue;
        }

        if ((c + (3 * dir.cDelt) >= columnSize) || (c + (3 * dir.cDelt) < 0)) {
            continue;
        }

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
            if ((c + dir.cDelt < 0) || (r + dir.rDelt < 0)) {
                break;
            }

            // check max bound
            if ((c + dir.cDelt >= columnSize) || (r + dir.rDelt >= rowSize)) {
                break;
            }

            // update to next coord
            c += dir.cDelt;
            r += dir.rDelt;
        }
    }

    return total;
}

bool isCross(const grid &wordGrid, int r, int c) {
    int diagonalsFound = 0;

    for (auto dia : diagonals) {
        // first char check min bounds
        if ((r - dia.rDelt < 0) || (c - dia.cDelt < 0)) {
            break;
        }

        // first char check inverse min bounds
        if ((r - dia.rDelt >= wordGrid.size()) ||
            (c - dia.cDelt > wordGrid[0].size())) {
            break;
        }

        // third char check min bounds
        if ((r + dia.rDelt < 0) || (c + dia.cDelt < 0)) {
            break;
        }

        // third char check inverse min bounds
        if ((r + dia.rDelt >= wordGrid.size()) ||
            (c + dia.cDelt > wordGrid[0].size())) {
            break;
        }

        char firstChar = wordGrid[r - dia.rDelt][c - dia.cDelt];
        char secondChar = wordGrid[r][c];
        char thirdChar = wordGrid[r + dia.rDelt][c + dia.cDelt];

        // at this point we are guaranteed our bounds are going to be valid
        if (firstChar == 'M' && secondChar == 'A' && thirdChar == 'S') {
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
    int nRows = wordGrid.size();
    int nColumns = wordGrid[0].size();
    int sum = 0;

    // iterate over every starting point in the grid
    for (size_t r = 0; r < nRows; r++) {
        for (size_t c = 0; c < nColumns; c++) {
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
            if (wordGrid[r][c] == 'A') {
                if (isCross(wordGrid, r, c)) {
                    sum++;
                }
            }
        }
    }

    return sum;
}
