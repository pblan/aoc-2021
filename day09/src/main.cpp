#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

bool is_in(int y, int x, std::set<std::tuple<int, int>> s) {
    for (auto i : s) {
        if (std::get<0>(i) == y && std::get<1>(i) == x) {
            return true;
        }
    }
    return false;
}

void check_neighbours(int y, int x, std::set<std::tuple<int, int>>& s, std::vector<std::vector<int>>& grid) {
    if (y < 1 || x < 1 || y >= grid.size() || x >= grid[0].size()) {
        return;
    }

    if (grid[y - 1][x] > grid[y][x] && grid[y - 1][x] != 9 && grid[y - 1][x] != INT_MAX && !is_in(y - 1, x, s)) {
        s.insert(std::make_tuple(y - 1, x));
        check_neighbours(y - 1, x, s, grid);
    }

    if (grid[y + 1][x] > grid[y][x] && grid[y + 1][x] != 9 && grid[y + 1][x] != INT_MAX && !is_in(y + 1, x, s)) {
        s.insert(std::make_tuple(y + 1, x));
        check_neighbours(y + 1, x, s, grid);
    }

    if (grid[y][x - 1] > grid[y][x] && grid[y][x - 1] != 9 && grid[y][x - 1] != INT_MAX && !is_in(y, x - 1, s)) {
        s.insert(std::make_tuple(y, x - 1));
        check_neighbours(y, x - 1, s, grid);
    }

    if (grid[y][x + 1] > grid[y][x] && grid[y][x + 1] != 9 && grid[y][x + 1] != INT_MAX && !is_in(y, x + 1, s)) {
        s.insert(std::make_tuple(y, x + 1));
        check_neighbours(y, x + 1, s, grid);
    }

    return;
}

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);
    auto row_size = input[0].size();

    std::vector<std::vector<int>> matrix{};

    for (int i = 0; i <= input.size() + 1; i++) {
        std::vector<int> row;
        for (int j = 0; j <= row_size + 1; j++) {
            if (i == 0 || j == 0 || i == (input.size() + 1) || j == (row_size + 1)) {
                row.push_back(INT_MAX);
            } else {
                row.push_back(input[i-1][j-1] - '0');
            }
        }
        matrix.push_back(row);
    }

    int sum = 0;

    for (int i = 1; i < matrix.size() - 1; i++) {
        for (int j = 1; j < matrix[i].size() - 1; j++) {
            if (matrix[i][j] < matrix[i - 1][j] && matrix[i][j] < matrix[i][j - 1] && matrix[i][j] < matrix[i + 1][j] && matrix[i][j] < matrix[i][j + 1]) {
                sum += matrix[i][j] + 1;
            }
        }
    }

    return sum;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);
    auto row_size = input[0].size();

    std::vector<std::vector<int>> matrix{};

    for (int i = 0; i <= input.size() + 1; i++) {
        std::vector<int> row;
        for (int j = 0; j <= row_size + 1; j++) {
            if (i == 0 || j == 0 || i == (input.size() + 1) || j == (row_size + 1)) {
                row.push_back(INT_MAX);
            } else {
                row.push_back(input[i-1][j-1] - '0');
            }
        }
        matrix.push_back(row);
    }

    std::vector<int> basin_sizes{};

    for (int i = 1; i < matrix.size() - 1; i++) {
        for (int j = 1; j < matrix[i].size() - 1; j++) {
            if (matrix[i][j] < matrix[i - 1][j] && matrix[i][j] < matrix[i][j - 1] && matrix[i][j] < matrix[i + 1][j] && matrix[i][j] < matrix[i][j + 1]) {

                std::set<std::tuple<int, int>> positions{};
                positions.insert(std::make_tuple(i, j));

                check_neighbours(i, j, positions, matrix);

                basin_sizes.push_back(positions.size());
            }
        }
    }

    std::sort(basin_sizes.begin(), basin_sizes.end());
    std::reverse(basin_sizes.begin(), basin_sizes.end());

    return basin_sizes[0] * basin_sizes[1] * basin_sizes[2];
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 15) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 1134) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}