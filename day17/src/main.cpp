#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

// split string
std::vector<std::string> split(const std::string &s, const std::string &delim) {
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len) {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0) {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

static std::tuple<int, int> task(std::string filename) {

    auto input = Input<std::string>(filename);
    
    int x_min{}, x_max, y_min{}, y_max{};

    for (auto line : input) {
        if (line[0] == 'x') {
            auto x_range = line.substr(2);
            auto x_range_split = split(x_range, "..");
            x_min = std::stoi(x_range_split[0]);
            x_max = std::stoi(x_range_split[1]);    
        } 
        
        if (line[0] == 'y') {
            auto y_range = line.substr(2);
            auto y_range_split = split(y_range, "..");
            y_min = std::stoi(y_range_split[0]);
            y_max = std::stoi(y_range_split[1]);
        }
    }

    std::cout << "x_min: " << x_min << " x_max: " << x_max << " y_min: " << y_min << " y_max: " << y_max << std::endl;

    // x_vel decreases by 1 if x_min > 0, increases by 1 if x_max < 0
    // y_vel decreases by 1 due to gravity

    // starting point is (0, 0)

    auto shoot = [&](int dx, int dy) {
        int x{0}, y{0}, max{0};

        //std::cout << "dx: " << dx << " dy: " << dy << std::endl;

        // while we don't overshoot the range
        while (x <= x_max && y_min <= y) {
            //std::cout << "\tx: " << x << " y: " << y << std::endl;
            x += dx;
            y += dy;

            max = std::max(max, y);

            if (dx) dx += (dx > 0) ? -1 : 1;
            dy--;

            // if within range
            if (x_min <= x && x <= x_max && y_min <= y && y <= y_max) {
                return max;
            }
        }

        return -1;
    };

    int res1{}, res2{};

    for (int y = y_min; y <= -y_min; y++) {
        for (int x = 0; x <= x_max; x++) {
            auto res = shoot(x, y);
            if (res != -1) {
                res1 = std::max(res1, res);
                res2++;
            }
            std::cout << "x: " << x << " y: " << y << " res: " << res1 << std::endl;
        }
    }
    
    return {res1, res2};
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto [test_answer1, test_answer2] = task("test_input.txt");
    auto [answer1, answer2] = task("input.txt");
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 45) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 112) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}