#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include <util.h>

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);

    std::vector<size_t> counter(input[0].size());

    for (size_t i = 0; i < input.size(); ++i) {
        for (size_t j = 0; j < input[i].size(); ++j) {
            if (input[i][j] == '1') {
                ++counter[j];
            }
        }
    }
    
    std::string gamma;
    std::string epsilon;
    for (size_t j = 0; j < input[0].size(); ++i) {
        if (counter[j] > input.size() / 2) {
            gamma += '1';
            epsilon += '0';
        } else {
            gamma += '0';
            epsilon += '1';
        }
    }
    
    return std::stoi(gamma, nullptr, 2) * std::stoi(epsilon, nullptr, 2);
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);

    auto oxygen = input.raw;
    auto co2 = input.raw;
    
    for (size_t i = 0; i < input[0].size(); ++i) {

        auto one_majority = std::count_if(oxygen.begin(), oxygen.end(), [&](const std::string& s) { return s[i] == '1'; }) * 2 >= oxygen.size();

        std::erase_if(oxygen, [&](auto vec) { return one_majority ? vec[i] == '0' : vec[i] == '1'; });
        if (oxygen.size() == 1) {
            break;
        }
    }

    for (size_t i = 0; i < input[0].size(); ++i) {

        auto one_minority = std::count_if(co2.begin(), co2.end(), [&](const std::string& s) { return s[i] == '1'; }) * 2 < co2.size();

        std::erase_if(co2, [&](auto vec) { return one_minority ? vec[i] == '0' : vec[i] == '1'; });
        if (co2.size() == 1) {
            break;
        }
    }

    return std::stoi(oxygen[0], nullptr, 2) * std::stoi(co2[0], nullptr, 2);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 198) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 230) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}