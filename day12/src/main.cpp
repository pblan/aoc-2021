#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>
#include <tuple>

#include <bits/stdc++.h>

#include <util.h>

struct state {
    std::string pos;
    std::set<std::string> rules;
    bool visited = false;
};

static std::tuple<uint32_t, uint32_t> task(std::string filename) {

    auto input = Input<std::string>(filename);

    // adjacency list
    std::map<std::string, std::vector<std::string>> adj;

    for (auto& line : input) {
        auto split = line.find("-");
        auto left = line.substr(0, split);
        auto right = line.substr(split + 1);

        if (right != "start") {
            adj[left].push_back(right);
        }

        if (left != "start") {
            adj[right].push_back(left);
        }
    }

    std::queue<state> queue{};
    // start state
    queue.push(state{"start", std::set<std::string>{"start"}, false});

    std::string pos;
    std::set<std::string> caves;
    bool already_found = false;
    int path_count1{}, path_count2{};

    while (!queue.empty()) {
        state current = queue.front();

        pos = current.pos;
        caves = current.rules;
        already_found = current.visited;

        //std::cout << "\npos: " << pos << " caves: " << caves.size() << std::endl;
        //std::cout << "[caves] ";
        //for (auto& s : caves) {
        //    std::cout << s << ", ";
        //}
        //std::cout << std::endl;
        //std::cout << "[ADJ] " << std::endl;
        //for (auto& n : adj[pos]) {
        //    std::cout << n << ": ";
        //    for (auto& v : adj[n]) {
        //        std::cout << v << ", ";
        //    }
        //    std::cout << std::endl;
        //}

        queue.pop();

        // found a path
        if (pos == "end") {
            if (!already_found) {
                path_count1++;
            }
            path_count2++;
        }

        else {
            for (auto& next : adj[pos]) {
                // filtering out all the lowercase caves
                if (std::islower(next[0])) {
                    if (caves.find(next) != caves.end()) {
                        // if not visited
                        if (!already_found) {
                            queue.push(state{next, caves, true});
                        }
                    }
                    else {
                        std::set<std::string> new_caves(caves);
                        new_caves.insert(next);
                        queue.push(state{next, new_caves, already_found});
                    }
                }
                else {
                    queue.push(state{next, caves, already_found});
                }
            }
        }
    }

    return {path_count1, path_count2};
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto [test_answer1, test_answer2] = task("test_input.txt");
    auto [answer1, answer2] = task("input.txt");

    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 226) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 3509) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}