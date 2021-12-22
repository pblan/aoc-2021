#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

#define fora(i, n) for (int i = 0; i < n; i++)

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);
    
    std::list<char> polymer;

    // input[0] is a string of chars
    for (auto c : input[0]) {
        polymer.push_back(c);
    }

    std::map<std::pair<char, char>, char> rules;

    for (int i = 1; i < input.size(); i += 3) {
        rules.insert({{input[i][0], input[i][1]}, input[i + 2][0]});
        std::cout << input[i][0] << " " << input[i][1] << " -> " << input[i + 2][0] << std::endl;
    }

    int steps = 10;

    fora(i, steps) {
        auto it = polymer.begin();
        while (it != polymer.end()) {
            auto next = it;
            next++;
            if (next == polymer.end()) {
                break;
            }
            auto rule = rules.find({*it, *next});
            if (rule != rules.end()) {
                //it = polymer.erase(it);
                //it = polymer.erase(it);
                ++it;
                polymer.insert(it, rule->second);
            } else {
                it++;
            }
            //std::cout << "Found rule: " << std::get<0>(rule->first) << std::get<1>(rule->first) << " -> " << rule->second << std::endl;
        }
        std::cout << "[" << i << "]" << "polymer: " << std::accumulate(polymer.begin(), polymer.end(), std::string("")) << std::endl;
    }

    // find most common char in polymer
    std::map<char, int> char_count;
    for (auto c : polymer) {
        char_count[c]++;
    }

    auto max_char = std::max_element(char_count.begin(), char_count.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
        return a.second < b.second;
    });

    std::cout << "Most common char: " << max_char->first << " (" << max_char->second << ")" << std::endl;

    // find least common char in polymer
    auto min_char = std::min_element(char_count.begin(), char_count.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
        return a.second < b.second;
    });

    std::cout << "Least common char: " << min_char->first << " (" << min_char->second << ")" << std::endl;

    return char_count[max_char->first] - char_count[min_char->first];
}

static unsigned long long int task2(std::string filename) {

    auto input = Input<std::string>(filename);
    
    // matrix named 'polymer' with all chars by 
    // default initialized to 0
    std::vector<std::vector<unsigned long long int>> polymer(26, std::vector<unsigned long long int>(26, 0));

    // input[0] is a string of chars
    for (int i = 0; i < input[0].size(); i++) {
        polymer[input[0][i] - 'A'][input[0][i + 1] - 'A']++;
    }

    std::cout << "Polymer matrix:" << std::endl;
    for (auto row : polymer) {
        for (auto c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    // parse rules
    std::map<std::pair<char, char>, char> rules;

    for (int i = 1; i < input.size(); i += 3) {
        rules.insert({{input[i][0], input[i][1]}, input[i + 2][0]});
        std::cout << input[i][0] << " " << input[i][1] << " -> " << input[i + 2][0] << std::endl;
    }

    fora (s, 40) {
        std::vector<std::vector<unsigned long long int>> changes(polymer);
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                auto x = (char)('A' + i), y = (char)('A' + j);

                if (polymer[i][j] == 0) {
                    continue;
                }

                // if there is a rule for this pair of chars
                if (rules.find({x, y}) != rules.end()) { 
                    // apply rule
                    auto rule = rules.find({x, y});

                    std::cout << "[" << s+1 << "] Found rule: " << std::get<0>(rule->first) << std::get<1>(rule->first) << " -> " << rule->second << std::endl;

                    changes[x - 'A'][y - 'A'] -= polymer[x - 'A'][y - 'A'];
                    changes[x - 'A'][rule->second - 'A'] += polymer[x - 'A'][y - 'A'];
                    changes[rule->second - 'A'][y - 'A'] += polymer[x - 'A'][y - 'A'];
                }
            }
        }
        // apply changes
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                polymer[i][j] = changes[i][j];
            }
        }

        //std::cout << "[" << i << "] " << "polymer: ";
        //for (auto row : polymer) {
        //    for (auto c : row) {
        //        std::cout << c << " ";
        //    }
        //    std::cout << std::endl;
        //}
    }

    // find most common char in polymer
    std::vector<std::pair<char, unsigned long long int>> char_count;
    for (int i = 0; i < 26; i++) {
        char_count.push_back({(char)('A' + i), 0});
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            char_count[i].second += polymer[i][j];
        }
    }

    // remove all chars that are not in the polymer
    for (auto it = char_count.begin(); it != char_count.end();) {
        if (it->second == 0) {
            it = char_count.erase(it);
        } else {
            ++it;
        }
    }

    // sort char_count by count
    std::sort(char_count.begin(), char_count.end(), [](const std::pair<char, unsigned long long int>& a, const std::pair<char, unsigned long long int>& b) {
        return a.second > b.second;
    });

    // print char_count
    for (auto c : char_count) {
        std::cout << c.first << " (" << c.second << ")" << std::endl;
    }

    std::cout << char_count.size() << std::endl;

    return char_count[0].second - char_count[char_count.size() - 1].second;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    unsigned long long int test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    unsigned long long int answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 1588) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 2188189693529) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}