#include <chrono>
#include <iostream>

#include <util.h>

static uint32_t task1(std::string filename) {

    auto input = Input<uint32_t>(filename);

    uint32_t answer{0};
    uint32_t prev = -1;

    for (auto curr : input) {
        answer += (curr > prev);
        prev = curr;
    }

    return answer;
}

static uint32_t task2(std::string filename) {

    auto input = Input<uint32_t>(filename);

    uint32_t answer{0};
    uint32_t prev_sum = -1;
    uint32_t new_sum;

    for (size_t i = 1; i < input.size() - 1; ++i) {
        new_sum = input[i-1] + input[i] + input[i+1];
        answer += (new_sum > prev_sum);
        prev_sum = new_sum;
    }

    return answer;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 7) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 5) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}