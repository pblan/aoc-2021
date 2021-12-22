#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

// std::map points to map closing brackets to points

std::map<int, int> points_1{
    {')', 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137},
};

std::map<int, int> points_2{
    {'(', 1},
    {'[', 2},
    {'{', 3},
    {'<', 4},
};

static uint32_t task1(std::string filename) {
    
    auto input = Input<std::string>(filename);

    int sum{};

    for (int i = 0; i < input.size(); ++i) {
        std::stack<char> brackets{};
        std::vector<char> closing{};

        for (auto c : input[i]) { 
             if (c == '{' || c == '[' || c == '(' || c == '<') {
                brackets.push(c);
            } else if (c == '}' || c == ']' || c == ')' || c == '>') {
                if (brackets.empty()) {
                    continue;
                }

                char expected = 0;
                switch (c) {
                    case '}':
                        expected = '{';
                        break;
                    case ']':
                        expected = '[';
                        break;
                    case ')':
                        expected = '(';
                        break;
                    case '>':
                        expected = '<';
                        break;
                }

                switch (brackets.top()) {
                    case '{':
                        if (c != '}') {
                            std::cout << "Expected '}' but found '" << c << "' instead" << " in " << input[i] << " -> " << i << std::endl;
                            sum += points_1[c];
                            break;
                        }
                        break;
                    case '[':
                        if (c != ']') {
                            std::cout << "Expected ']' but found '" << c << "' instead" <<  " in " << input[i] << " -> " << i << std::endl;
                            sum += points_1[c];
                            break;
                        }
                        break;
                    case '(':
                        if (c != ')') {
                            std::cout << "Expected ')' but found '" << c << "' instead" <<  " in " << input[i] << " -> " << i << std::endl;
                            sum += points_1[c];
                            break;
                        }
                        break;
                    case '<':
                        if (c != '>') {
                            std::cout << "Expected '>' but found '" << c << "' instead" <<  " in " << input[i] << " -> " << i << std::endl;
                            sum += points_1[c];
                            break;
                        }
                        break;
                }
                brackets.pop();
            }
        }
    }

    return sum;
}

static uint32_t task2(std::string filename) {
    
    auto input = Input<std::string>(filename);

    std::vector<long> result{};

    for (int i = 0; i < input.size(); ++i) {
        std::stack<char> brackets{};
        bool skip{false};

        for (auto c : input[i]) { 
             if (c == '{' || c == '[' || c == '(' || c == '<') {
                brackets.push(c);
            } else if (c == '}' || c == ']' || c == ')' || c == '>') {
                if (brackets.empty()) {
                    continue;
                }

                char expected = 0;
                switch (c) {
                    case '}':
                        expected = '{';
                        break;
                    case ']':
                        expected = '[';
                        break;
                    case ')':
                        expected = '(';
                        break;
                    case '>':
                        expected = '<';
                        break;
                }

                switch (brackets.top()) {
                    case '{':
                        if (c != '}') {
                            std::cout << "[SKIPPING] Expected '}' but found '" << c << "' instead" <<  " -> " << i << std::endl;
                            skip = true;
                            break;
                        }
                        break;
                    case '[':
                        if (c != ']') {
                            std::cout << "[SKIPPING] Expected ']' but found '" << c << "' instead" <<  " -> " << i << std::endl;
                            skip = true;
                            break;
                        }
                        break;
                    case '(':
                        if (c != ')') {
                            std::cout << "[SKIPPING] Expected ')' but found '" << c << "' instead" <<  " -> " << i << std::endl;
                            skip = true;
                            break;
                        }
                        break;
                    case '<':
                        if (c != '>') {
                            std::cout << "[SKIPPING] Expected '>' but found '" << c << "' instead" <<  " -> " << i << std::endl;
                            skip = true;
                            break;
                        }
                        break;
                }
                brackets.pop();
            }
        }

        if (skip) {
            continue;
        }

        long sum{};
        std::vector<char> closing{};

        while (!brackets.empty()) {
            char c = brackets.top();
            brackets.pop();
            switch (c) {
                case '{':
                    closing.push_back('}');
                    break;
                case '[':
                    closing.push_back(']');
                    break;
                case '(':
                    closing.push_back(')');
                    break;
                case '<':
                    closing.push_back('>');
                    break;
            }
            sum = sum * 5 + points_2[c];
            std::cout << sum << std::endl;
        }

        result.push_back(sum);
        std::cout << "Result: " << sum << std::endl;

        std::cout << input[i] << " - Complete by adding '";
        for (auto c : closing) {
            std::cout << c;
        }   
        std::cout << "'" << " -> " << i << std::endl;
    }

    // sorting result and taking the middle value
    std::sort(result.begin(), result.end());
    return result[result.size() / 2];
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 26397) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 288957) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}