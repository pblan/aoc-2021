#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include <util.h>

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);
    
    std::vector<std::vector<int>> matrix(1000, std::vector<int>(1000, 0));

    std::tuple<int, int> from{}, to{};

    for (int i = 0; i < input.size(); i += 3) {
        std::string from_str = input[i];
        from = std::make_tuple(std::stoi(from_str.substr(0, from_str.find(','))), std::stoi(from_str.substr(from_str.find(',') + 1)));

        std::string to_str = input[i + 2];
        to = std::make_tuple(std::stoi(to_str.substr(0, to_str.find(','))), std::stoi(to_str.substr(to_str.find(',') + 1)));
        
        // diagonal
        if (std::get<0>(from) != std::get<0>(to) && std::get<1>(from) != std::get<1>(to)) {
            continue;
        }
        else {   // horizontal or vertical
            for (int x = std::min(std::get<0>(from), std::get<0>(to)); x <= std::max(std::get<0>(from), std::get<0>(to)); ++x) {
                for (int y = std::min(std::get<1>(from), std::get<1>(to)); y <= std::max(std::get<1>(from), std::get<1>(to)); ++y) {
                    //if (x > matrix.size()) {
                    //    matrix.resize(x);
                    //}
                    //
                    //if (y > matrix[x].size()) {
                    //    matrix[x].resize(y);
                    //}

                    matrix[x][y]++;
                }
            }
        }
    }
    int counter{};

    for (auto& row : matrix) {
        counter += std::count_if(row.begin(), row.end(), [](int i) { return i > 1; });
    }

    //std::ofstream outfile;
    //outfile.open("matrix.ppm");
    //outfile << "P3\n" << matrix.size() << " " << matrix[0].size() << "\n255\n";
    //for (auto& row : matrix) {
    //    for (auto& col : row) {
    //        outfile << (col == 0 ? "255 255 255" : (col > 1 ? "255 0 0" : "0 0 255")) << " ";
    //    }
    //    outfile << "\n";
    //}
    //outfile.close();

    return counter;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);
    
    std::vector<std::vector<int>> matrix(1000, std::vector<int>(1000, 0));

    std::tuple<int, int> from{}, to{};

    for (int i = 0; i < input.size(); i += 3) {
        std::string from_str = input[i];
        from = std::make_tuple(std::stoi(from_str.substr(0, from_str.find(','))), std::stoi(from_str.substr(from_str.find(',') + 1)));


        std::string to_str = input[i + 2];
        to = std::make_tuple(std::stoi(to_str.substr(0, to_str.find(','))), std::stoi(to_str.substr(to_str.find(',') + 1)));
        
        // diagonal
        if (std::get<0>(from) != std::get<0>(to) && std::get<1>(from) != std::get<1>(to)) {
            int x = std::get<0>(from); 
            int y = std::get<1>(from);

            matrix[x][y]++;

            do {
                std::get<0>(from) < std::get<0>(to) ? x++ : x--;
                std::get<1>(from) < std::get<1>(to) ? y++ : y--;
                
                matrix[x][y]++;
            }
            while (x != std::get<0>(to) || y != std::get<1>(to));
        }
        else {   // horizontal or vertical
            for (int x = std::min(std::get<0>(from), std::get<0>(to)); x <= std::max(std::get<0>(from), std::get<0>(to)); ++x) {
                for (int y = std::min(std::get<1>(from), std::get<1>(to)); y <= std::max(std::get<1>(from), std::get<1>(to)); ++y) {
                    //if (x > matrix.size()) {
                    //    matrix.resize(x);
                    //}
                    //
                    //if (y > matrix[x].size()) {
                    //    matrix[x].resize(y);
                    //}

                    matrix[x][y]++;
                }
            }
        }
    }
    int counter{};

    for (auto& row : matrix) {
        counter += std::count_if(row.begin(), row.end(), [](int i) { return i > 1; });
    }

    std::ofstream outfile;
    outfile.open("matrix.ppm");
    outfile << "P3\n" << matrix.size() << " " << matrix[0].size() << "\n255\n";
    for (auto& row : matrix) {
        for (auto& col : row) {
            outfile << (col == 0 ? "255 255 255" : (col > 1 ? "255 0 0" : "0 0 255")) << " ";
        }
        outfile << "\n";
    }
    outfile.close();

    return counter;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 5) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 12) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}