#include "solution.hpp"
#include <iostream>
#include <ostream>
#include <string>

struct chunk {
    int id;
    int len;
};

std::vector<int> generateDiskImage(const std::string &target) {
    std::vector<int> diskImage;
    bool isBlock = true;
    size_t id = 0;

    for (const auto c : target) {
        int val = c - 48;
        for (size_t i = 0; i < val; i++) {
            if (isBlock) {
                diskImage.push_back(id);
            } else {
                diskImage.push_back(-1);
            }
        }
        if (isBlock) {
            id++;
        }
        isBlock = !isBlock;
    }

    return diskImage;
}

std::vector<chunk> generateDiskImageP2(const std::string &target) {
    bool isFile = true;
    size_t id = 0;
    std::vector<chunk> diskImage;

    for (const auto c : target) {
        int val = c - 48;
        if (isFile) {
            diskImage.push_back(chunk(id, val));
        } else {
            diskImage.push_back(chunk(-1, val));
        }
        if (isFile) {
            id++;
        }
        isFile = !isFile;
    }

    return diskImage;
}

void defragDisk(std::vector<int> &diskImage) {
    size_t start = 0;
    size_t right = diskImage.size() - 1;

    for (size_t left = 0; left < right; left++) {
        if (diskImage[left] == -1) {
            for (size_t j = right; j > left; j--) {
                if (diskImage[j] != -1) {
                    diskImage[left] = diskImage[j];
                    diskImage[j] = -1;
                    right = j - 1;
                    break;
                }
            }
        }

        if (left >= right) {
            break;
        }
    }
}

void defragDiskP2(std::vector<chunk> &diskImage) {
    for (int right = diskImage.size() - 1; right >= 0; right--) {
        // if its empty space we dont need to move it
        if (diskImage[right].id == -1)
            continue;

        for (int left = 0; left < right; left++) {
            int diff = diskImage[left].len - diskImage[right].len;
            if (diskImage[left].id == -1 && diff >= 0) {

                
                diskImage[left] = chunk(diskImage[right].id, diskImage[right].len);
                diskImage[right] = chunk(-1, diskImage[right].len);

                // fix the space difference
                if (diff > 0) {
                    diskImage.insert(diskImage.begin() + left + 1,
                                     chunk(-1, diff));
                    right += 1;
                }

                break;
            }
        }
    }
}

int64_t calcChecksumP2(const std::vector<chunk> &target) {
    int64_t checksum = 0;
    int position = 0;

    for (const auto &chunk : target) {
        if (chunk.id != -1) {
            int64_t chunkSum = 0;
            for (int i = 0; i < chunk.len; i++) {
                chunkSum += static_cast<int64_t>(position + i) * chunk.id;
            }
            checksum += chunkSum;
        }
        position += chunk.len;
    }
    return checksum;
}

int64_t calcChecksum(const std::vector<int> &target) {
    int64_t checksum = 0;
    for (int i = 0; i < target.size(); i++) {
        if (target[i] != -1) {
            checksum += (i * target[i]);
        }
    }
    return checksum;
}

int64_t Solution::solvePart1(const std::vector<std::string> &input) {
    std::vector<int> diskImage = generateDiskImage(input[0]);
    defragDisk(diskImage);

    return calcChecksum(diskImage);
}

int64_t Solution::solvePart2(const std::vector<std::string> &input) {
    std::vector<chunk> diskImage = generateDiskImageP2(input[0]);
    defragDiskP2(diskImage);

    return calcChecksumP2(diskImage);
}
