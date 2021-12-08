#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

static bool contains(const std::string& str, const std::string& substr) {
    return std::all_of(substr.begin(), substr.end(), [&](char c) {
        return str.find(c) != std::string::npos;
    });
}

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);

    std::vector<std::vector<std::string>> signal{};
    std::vector<std::vector<std::string>> output{};

    for (int i = 0; i <= input.size() / 15; i++) { // 15 is the length of the signal
        std::vector<std::string> s{input.begin() + i * 15, input.begin() + i * 15 + 10};
        std::vector<std::string> o{input.begin() + i * 15 + 11, input.begin() + i * 15 + 11 + 4};
        
        signal.push_back(s);
        output.push_back(o);
    }

    std::set<int> numbers{ { 2, 3, 4, 7 } };

    int count{};
    
    for (auto& o : output) {
        count += std::count_if(o.begin(), o.end(), [&numbers](std::string s) {
            return numbers.find(s.length()) != numbers.end();
        });
    }
    return count;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);

    std::vector<std::vector<std::string>> signal{};
    std::vector<std::vector<std::string>> output{};

    for (int i = 0; i <= input.size() / 15; i++) { // 15 is the length of the signal
        std::vector<std::string> s{input.begin() + i * 15, input.begin() + i * 15 + 10};
        std::vector<std::string> o{input.begin() + i * 15 + 11, input.begin() + i * 15 + 11 + 4};
        
        signal.push_back(s);
        output.push_back(o);
    }

    int sum{};

    for (int i = 0; i < signal.size() - 1; i++) {
        std::map<int, std::string> found_mapping{};
        std::vector<std::string> missing_mapping{};

        // seeing what we can definitely map
        for (auto& pattern : signal[i]) {
            if (pattern.length() == 2) { // pattern for 1
                found_mapping.insert({1, pattern});
                //std::cout << "Found mapping for 1: " << pattern << std::endl;
            }
            else if (pattern.length() == 4) { // pattern for 4
                found_mapping.insert({4, pattern});
                //std::cout << "Found mapping for 4: " << pattern << std::endl;
            }
            else if (pattern.length() == 3) { // pattern for 7
                found_mapping.insert({7, pattern});
                //std::cout << "Found mapping for 7: " << pattern << std::endl;
            }
            else if (pattern.length() == 7) { // pattern for 8
                found_mapping.insert({8, pattern});
                //std::cout << "Found mapping for 8: " << pattern << std::endl;
            }
            else {
                missing_mapping.push_back(pattern);
            }
        }

        // see if we can map the missing patterns
        while (missing_mapping.size() > 0) {
            auto current_pattern = missing_mapping.front();
            missing_mapping.erase(missing_mapping.begin());

            // length = 6 => 0, 6 or 9
            if (current_pattern.length() == 6) {
                // 4 fits => 9
                if (contains(current_pattern, found_mapping[4])) {
                    found_mapping.insert({9, current_pattern});
                    //std::cout << "Found mapping for 9: " << current_pattern << std::endl;
                }
                // if mapping for 5 exists ...
                else if (found_mapping.count(5) > 0) {
                    // ... and it fits => 6
                    if (contains(current_pattern, found_mapping[5])) {
                        found_mapping.insert({6, current_pattern});
                        //std::cout << "Found mapping for 6: " << current_pattern << std::endl;
                    }
                    // ... and it doesn't fit => 0
                    else {
                        found_mapping.insert({0, current_pattern});
                        //std::cout << "Found mapping for 0: " << current_pattern << std::endl;
                    }
                }
                else {
                    missing_mapping.push_back(current_pattern);
                }
            }
            // length = 5 => 2, 3 or 5
            else if (current_pattern.length() == 5) {
                // if 1 fits => 3
                if (contains(current_pattern, found_mapping[1])) {
                    found_mapping.insert({3, current_pattern});
                    //std::cout << "Found mapping for 3: " << current_pattern << std::endl;
                }
                // if mapping for 9 exists ...
                else if (found_mapping.count(9) > 0) {
                    // ... and it curr fits into it => 5
                    if (contains(found_mapping[9], current_pattern)) {
                        found_mapping.insert({5, current_pattern});
                        //std::cout << "Found mapping for 5: " << current_pattern << std::endl;
                    }
                    else {
                        found_mapping.insert({2, current_pattern});
                        //std::cout << "Found mapping for 2: " << current_pattern << std::endl;
                    }
                }
                else {
                    missing_mapping.push_back(current_pattern);
                }
            }
        }

        std::string partial_sum{};
        for (auto& o : output[i]) {
            for (auto& key : found_mapping) {
                auto sorted_o = o;
                auto sorted_key = key.second;

                std::sort(sorted_o.begin(), sorted_o.end());
                std::sort(sorted_key.begin(), sorted_key.end());
                
                if (sorted_o == sorted_key) {
                    partial_sum += std::to_string(key.first);
                    break;
                }
            }
        }
        sum += std::stoi(partial_sum);
    }
    return sum;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 26) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 61229) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}