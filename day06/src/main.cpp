#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>

#include <util.h>

const int DAYS_1 = 80;
const int DAYS_2 = 256;

static uint32_t task1(std::string filename) {
    auto input = Input<std::string>(filename);

    std::string fish;
    for (int i = 0; i < input[0].size(); ++i) {
        if (input[0][i] != ',') {
            fish.push_back(input[0][i]);
        }
    }    

    for (int i = 1; i <= DAYS_1; ++i) {
        int size = fish.size();
        for (int j = 0; j < size; ++j) {
            if (fish[j] == '0') {
                fish[j] = '6';
                fish.push_back('8');
            }
            else {
                fish[j]--;
            }
        }
    }
    
    return fish.size();
}

static long long task2(std::string filename) {
    auto input = Input<std::string>(filename);

    std::vector<long long> fish{};

    for (int i = 0; i < 9; ++i) {
        fish.push_back(std::count(input[0].begin(), input[0].end(), i + '0'));
    }

    for (int i = 1; i <= DAYS_2; ++i) {
        const long long babies = fish[0];

        for (int i = 1; i < 7; i++) {
            fish[i-1] = fish[i];
        }

        fish[6] = babies + fish[7];
        fish[7] = fish[8];
        fish[8] = babies;
    }
    
    long long sum{};
    for (int i = 0; i < fish.size(); ++i) {
        sum += fish[i];
    }
    return sum;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    long long test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    long long answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 5934) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 26984457539) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}