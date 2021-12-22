#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

static void flash(int i, int j, std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>& seen, int& counter) {
    if (seen[i][j]) return;
    if (matrix[i][j] <= 9) return;

    seen[i][j] = true;
    counter++;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int ii = i + dx;
            int jj = j + dy;

            if (ii < 0 || ii >= matrix.size() || jj < 0 || jj >= matrix[0].size()) continue;
        
            matrix[ii][jj]++;
            flash(ii, jj, matrix, seen, counter);
        }
    }
}


static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);

    auto n = input.size();
    auto m = input[0].size();

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(m));

    int counter{};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = input[i][j] - '0';
        }
    }

    auto steps = 100;

    for (int _ = 1; _ <= steps; ++_) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrix[i][j]++;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                seen[i][j] = false;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                flash(i, j, matrix, seen, counter);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j] > 9) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    
    return counter;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);

    auto n = input.size();
    auto m = input[0].size();

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(m));

    int counter{};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = input[i][j] - '0';
        }
    }

    auto steps = 1000000;

    for (int _ = 1; _ <= steps; ++_) {

        int simultaneous = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrix[i][j]++;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                seen[i][j] = false;
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                flash(i, j, matrix, seen, counter);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j] > 9) {
                    simultaneous++;
                    matrix[i][j] = 0;
                }
            }
        }
        
        if (simultaneous == n * m) {
            return _;
        }
    }
    return 0;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t answer1{task1("input.txt")};

    uint32_t test_answer2{task2("test_input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 1656) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 195) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}