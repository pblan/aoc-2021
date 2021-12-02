#include <chrono>
#include <iostream>

#include <util.h>

const std::string FORWARD{"forward"};
const std::string DOWN{"down"};
const std::string UP{"up"};

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);

    int32_t x{0};
    int32_t z{0};    

    for (size_t i = 0; i < input.size() - 1; i += 2) {
        auto direction = input[i];
        auto value = std::stoi(input[i + 1]);

        x += (direction == FORWARD) * value;
        z += (direction == UP) ? -value : ((direction == DOWN) ? value : 0);
    }

    return x * z;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);

    int32_t x{0};
    int32_t z{0};    
    int32_t aim{0};    

    for (size_t i = 0; i < input.size() - 1; i += 2) {
        auto direction = input[i];
        auto value = std::stoi(input[i + 1]);

        aim += (direction == UP) ? -value : ((direction == DOWN) ? value : 0);
        x += (direction == FORWARD) * value;
        z += (direction == FORWARD) * value * aim;
    }

    return x * z;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 150) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 900) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}