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

    int n{}, m{};
    std::vector<std::tuple<int, int>> coords{};
    std::vector<std::string> folds{};

    for (int i = 0; i < input.size(); ++i) {

        auto line = input[i];

        if (line == "fold") {
            folds.push_back(input[i + 2]);
            i += 2;
            continue;
        }

        int x{}, y{};
        x = std::stoi(line.substr(0, line.find(',')));
        y = std::stoi(line.substr(line.find(',') + 1));

        coords.push_back(std::make_tuple(x, y));

        n = std::max(n, x);
        m = std::max(m, y);
    }
    
    std::vector<std::vector<bool>> matrix(m + 1, std::vector<bool>(n + 1, false));

    //std::cout << "n: " << n << " m: " << m << std::endl;
    //std::cout << "folds: " << folds.size() << std::endl;

    for (auto coord : coords) {
        int x{}, y{};
        std::tie(x, y) = coord;
        matrix[y][x] = true;
    }

    for (auto& f : folds) {
        int pos{};
        if (f[0] == 'x') {
            pos = std::stoi(f.substr(2));

            for (int i = 0; i < m + 1; ++i) {
                for (int j = 0; j < n + 1; ++j) {
                    matrix[i][j] = matrix[i][n - j] || matrix[i][j];
                }
            }

            n = n - pos - 1;
        }

        if (f[0] == 'y') {
            pos = std::stoi(f.substr(2));

            for (int i = 0; i < m + 1; ++i) {
                for (int j = 0; j < n + 1; ++j) {
                    matrix[i][j] = matrix[m - i][j] || matrix[i][j];
                }
            }

            m = m - pos - 1;
        }

        break;
    }

    // count number of true coordinates
    int count{};

    for (int i = 0; i < m + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            if (matrix[i][j]) {
                count++;
            }
        }
    }

    return count;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);

    int n{}, m{};
    std::vector<std::tuple<int, int>> coords{};
    std::vector<std::string> folds{};

    for (int i = 0; i < input.size(); ++i) {

        auto line = input[i];

        if (line == "fold") {
            folds.push_back(input[i + 2]);
            i += 2;
            continue;
        }

        int x{}, y{};
        x = std::stoi(line.substr(0, line.find(',')));
        y = std::stoi(line.substr(line.find(',') + 1));

        coords.push_back(std::make_tuple(x, y));

        n = std::max(n, x);
        m = std::max(m, y);
    }
    
    // matrix of dimensions n x m
    std::vector<std::vector<bool>> matrix(m + 1, std::vector<bool>(n + 1, false));

    //std::cout << "n: " << n << " m: " << m << std::endl;
    //std::cout << "folds: " << folds.size() << std::endl;

    for (auto c : coords) {
        int x{}, y{};
        std::tie(x, y) = c;
        matrix[y][x] = true;
    }

    // fold
    for (auto& f : folds) {
        int pos{};
        if (f[0] == 'x') {
            pos = std::stoi(f.substr(2));

            for (int i = 0; i < m + 1; ++i) {
                for (int j = 0; j < n + 1; ++j) {
                    matrix[i][j] = matrix[i][n - j] || matrix[i][j];
                }
            }

            n = n - pos - 1;
        }

        if (f[0] == 'y') {
            pos = std::stoi(f.substr(2));

            for (int i = 0; i < m + 1; ++i) {
                for (int j = 0; j < n + 1; ++j) {
                    matrix[i][j] = matrix[m - i][j] || matrix[i][j];
                }
            }

            m = m - pos - 1;
        }
    }
    

    // print matrix
    for (int i = 0; i < m + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            std::cout << (matrix[i][j] ? '#' : '.');
        }
        std::cout << std::endl;
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 17) << std::endl;
    std::cout << "[Test] Task 2: " << std::endl;
    task2("test_input.txt");


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << std::endl;
    task2("input.txt");
}