#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

const std::vector<std::vector<int>> rot_x = {
    {1, 0, 0},
    {0, 0, -1},
    {0, 1, 0}
};

const std::vector<std::vector<int>> rot_y = {
    {0, 0, 1},
    {0, 1, 0},
    {-1, 0, 0}
};

const std::vector<std::vector<int>> rot_z = {
    {0, -1, 0},
    {1, 0, 0},
    {0, 0, 1}
};

const std::vector<std::vector<int>> mirror_x = {
    {1, 0, 0},
    {0, -1, 0},
    {0, 0, -1}
};

const std::vector<std::vector<int>> mirror_y = {
    {-1, 0, 0},
    {0, 1, 0},
    {0, 0, -1}
};

const std::vector<std::vector<int>> mirror_z = {
    {-1, 0, 0},
    {0, 0, 1},
    {0, -1, 0}
};

static std::tuple<int, int, int> split(const std::string& s, char delimiter) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return std::make_tuple(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]));
}

// rotate tuple around given axis n times
static std::tuple<int, int, int> rotate(const std::tuple<int, int, int>& t, const std::vector<std::vector<int>>& rot, int n) {
    std::tuple<int, int, int> res = t;
    for (int i = 0; i < n; i++) {
        res = std::make_tuple(std::get<0>(res) * rot[0][0] + std::get<1>(res) * rot[0][1] + std::get<2>(res) * rot[0][2],
                              std::get<0>(res) * rot[1][0] + std::get<1>(res) * rot[1][1] + std::get<2>(res) * rot[1][2],
                              std::get<0>(res) * rot[2][0] + std::get<1>(res) * rot[2][1] + std::get<2>(res) * rot[2][2]);
    }

    //std::cout << "rotate(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ") -> " << std::get<0>(res) << ", " << std::get<1>(res) << ", " << std::get<2>(res) << std::endl;
    return res;
}

// x, y, z offset
static std::tuple<int, int, int> translate(const std::tuple<int, int, int>& t, int x, int y, int z) {
    return std::make_tuple(std::get<0>(t) + x, std::get<1>(t) + y, std::get<2>(t) + z);
}

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);

    std::vector<std::vector<std::tuple<int, int, int>>> scanner_values;
    
    // parse input file into scanner_values
    std::vector<std::tuple<int, int, int>> curr_values;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "---") {
            i += 4;
        }
        // 404,-588,-901 to tuple 
        curr_values.push_back(split(input[i], ','));
        if (input[i+1] == "---" || i + 1 == input.size()) {
            scanner_values.push_back(curr_values);
            curr_values.clear();
        }
    }

    /*
    // print all scanner values
    for (auto& scanner : scanner_values) {

        std::cout << "\n\n\nscanner:\n";

        for (auto& value : scanner) {
            std::cout << std::get<0>(value) << "," << std::get<1>(value) << "," << std::get<2>(value) << std::endl;
        }
    }
    */
    
    // store orientation for each scanner in relation to scanner 0
    // rotation x, rotation y, rotation z, mirror x, mirror y, mirror z
    std::vector<std::tuple<int, int, int, int, int, int>> scanner_orientations;
    
    // check for each scanner i if there are at least 12 matching values after applying the rotations or mirrors with the scanner 0
    // if yes, store the orientation of the scanner in relation to scanner 0

    // for each scanner other than scanner 0
    for (int i = 1; i < scanner_values.size(); i++) {
        int matching_values = 0;

        // use matrix multiplication to check if the scanner value matches the scanner 0 value after applying the rotations or mirrors with the scanner 0
        
        // rotate around x-axis up to 3 times
        for (int j = 1; j <= 3; j++) {
            // rotate around y-axis up to 3 times
            for (int k = 1; k <= 3; k++) {
                // rotate around z-axis up to 3 times
                for (int l = 1; l <= 3; l++) {
                    // mirror around x-axis
                    for (int m = 0; m <= 1; m++) {
                        // mirror around y-axis
                        for (int n = 0; n <= 1; n++) {
                            // mirror around z-axis
                            for (int o = 0; o <= 1; o++) {
                                for (auto& value : scanner_values[i]) {
                                    // apply rotation
                                    value = rotate(value, rot_x, j);
                                    value = rotate(value, rot_y, k);
                                    value = rotate(value, rot_z, l);
                                    // apply mirror
                                    value = rotate(value, mirror_x, m);
                                    value = rotate(value, mirror_y, n);
                                    value = rotate(value, mirror_z, o);

                                    
                                    // offset x from -1000 to 1000
                                    for (int p = -1000; p <= 1000; p++) {
                                        // offset y from -1000 to 1000
                                        for (int q = -1000; q <= 1000; q++) {
                                            // offset z from -1000 to 1000
                                            for (int r = -1000; r <= 1000; r++) {
                                                // apply translation
                                                value = translate(value, p, q, r);

                                                // check if value is in scanner 0
                                                if (std::find(scanner_values[0].begin(), scanner_values[0].end(), value) != scanner_values[0].end()) {
                                                    matching_values++;
                                                }

                                                if (matching_values >= 12) {
                                                    scanner_orientations.push_back(std::make_tuple(j, k, l, m, n, o));
                                                    goto end;
                                                }
                                            }
                                        }
                                    }

                                    
                                }
                            }
                        }
                    }
                }
            }
        }
        end:
        std::cout << "matching values: " << matching_values << std::endl;
    }

    // print all scanner orientations
    for (auto& scanner : scanner_orientations) {

        std::cout << "\n\n\nscanner:\n";

        std::cout << std::get<0>(scanner) << "," << std::get<1>(scanner) << "," << std::get<2>(scanner) << std::endl;
    }

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