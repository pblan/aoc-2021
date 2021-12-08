#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);
    
    // split input at ',' into vector of int
    std::vector<int> positions;
    std::stringstream ss(input[0]);
    std::string token;
    while (std::getline(ss, token, ',')) {
        positions.push_back(std::stoi(token));
    }

    int min_sum = INT_MAX;
    int max_pos = *std::max_element(positions.begin(), positions.end());

    for (int i = 0; i < max_pos; ++i) {
        int sum = 0;
        for (int j = 0; j < positions.size(); ++j) {
            sum += abs(positions[j] - i);
        }
        if (sum < min_sum) {
            min_sum = sum;
        }
    }

    return min_sum;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);
    
    std::vector<int> positions;
    std::stringstream ss(input[0]);
    std::string token;
    while (std::getline(ss, token, ',')) {
        positions.push_back(std::stoi(token));
    }

    int min_sum = INT_MAX;
    int max_pos = *std::max_element(positions.begin(), positions.end());

    for (int i = 0; i < max_pos; ++i) {
        int sum = 0;

        for (int j = 0; j < positions.size(); ++j) {
            auto dist = std::abs(positions[j] - i);
            // Gauss's formula
            sum += (dist * (dist + 1)) / 2;
        }
        if (sum < min_sum) {
            min_sum = sum;
        }
    }

    return min_sum;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 37) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 168) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}