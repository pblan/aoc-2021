#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

static std::vector<std::pair<int, int>> get_neighbors(std::pair<int, int> pos, std::vector<std::vector<int>>& grid) {
    std::vector<std::pair<int, int>> neighbors;
    // up
    if (pos.first > 0) {
        neighbors.push_back({pos.first - 1, pos.second});
    }
    // down
    if (pos.first < grid.size() - 1) {
        neighbors.push_back({pos.first + 1, pos.second});
    }
    // left
    if (pos.second > 0) {
        neighbors.push_back({pos.first, pos.second - 1});
    }
    // right
    if (pos.second < grid[0].size() - 1) {
        neighbors.push_back({pos.first, pos.second + 1});
    }
    return neighbors;
}

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);

    // split into vector of vectors
    std::vector<std::vector<int>> grid;

    for (auto line : input) {
        std::vector<int> row;
        for (auto c : line) {
            row.push_back(c - '0');
        }
        grid.push_back(row);
    }

    int m = grid.size() - 1;
    int n = grid[0].size() - 1;

    std::map<std::pair<int, int>, int> dist;
    std::map<std::pair<int, int>, std::pair<int, int>> prev;

    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> queue;
    queue.push({0, {0, 0}});
    dist[std::make_pair(0, 0)] = 0;

    while (!queue.empty()) {
        auto curr = queue.top();
        queue.pop();

        auto neighbors = get_neighbors(curr.second, grid);
        for (auto neighbor : neighbors) {
            if (grid[neighbor.first][neighbor.second] == 0) {
                continue;
            }
            auto new_dist = dist[curr.second] + grid[neighbor.first][neighbor.second];
            if (dist.find(neighbor) == dist.end() || new_dist < dist[neighbor]) {
                dist[neighbor] = new_dist;
                prev[neighbor] = curr.second;
                queue.push({new_dist, neighbor});
            }
        }
    }

    return dist[std::make_pair(m, n)];
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);

    // split into vector of vectors
    std::vector<std::vector<int>> grid;

    // repeat the input 5x5 times
    for (int i = 0; i < 5; i++) {
        for (auto line : input) {
            std::vector<int> row;

            for (int j = 0; j < 5; j++) {
                for (auto c : line) {
                    auto new_c = (c - '0' + i + j) % 9;
                    new_c = new_c == 0 ? 9 : new_c;
                    row.push_back(new_c);
                }
            }
            grid.push_back(row);
        }
    }

    int m = grid.size() - 1;
    int n = grid[0].size() - 1;

    std::map<std::pair<int, int>, int> dist;
    std::map<std::pair<int, int>, std::pair<int, int>> prev;

    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> queue;
    queue.push({0, {0, 0}});
    dist[std::make_pair(0, 0)] = 0;

    while (!queue.empty()) {
        // curr is of the form (distance, (x, y))
        auto curr = queue.top();
        queue.pop();

        auto neighbors = get_neighbors(curr.second, grid);
        for (auto neighbor : neighbors) {
            if (grid[neighbor.first][neighbor.second] == 0) {
                continue;
            }
            auto new_dist = dist[curr.second] + grid[neighbor.first][neighbor.second];
            if (dist.find(neighbor) == dist.end() || new_dist < dist[neighbor]) {
                dist[neighbor] = new_dist;
                prev[neighbor] = curr.second;
                queue.push({new_dist, neighbor});
            }
        }
    }

    // visualize
    std::vector<std::pair<int, int>> path;
    auto curr = std::make_pair(m, n);
    while (curr != std::make_pair(0, 0)) {
        path.push_back(curr);
        curr = prev[curr];
    }
    std::reverse(path.begin(), path.end());

    std::vector<std::vector<bool>> bool_grid(m + 1, std::vector<bool>(n + 1, false));

    // set all visited nodes to true
    for (auto p : path) {
        bool_grid[p.first][p.second] = true;
    }

    // generate ppm file from bool_grid
    std::ofstream ppm_file;
    ppm_file.open("output.ppm");
    ppm_file << "P3\n" << m + 1 << " " << n + 1 << "\n255\n";
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (bool_grid[i][j]) {
                ppm_file << "255 255 255 ";
            } else {
                ppm_file << "0 0 0 ";
            }
        }
        ppm_file << "\n";
    }

    return dist[std::make_pair(m, n)];
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 40) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 315) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}