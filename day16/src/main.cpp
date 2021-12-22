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
    
    return 0;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);
    
    return 0;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    //uint32_t answer1{task1("input.txt")};
    //uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 0) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 0) << std::endl;


    //std::cout << "Task 1: " << answer1 << std::endl;
    //std::cout << "Task 2: " << answer2 << std::endl;
}