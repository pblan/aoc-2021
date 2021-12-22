#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>

#include <bits/stdc++.h>

#include <util.h>

bool lit = false;

// function to get binary number of square around pixel from image
static int get_binary_number(const std::vector<std::vector<bool>>& image, int x, int y) {
    // binary number is read left to right, top to bottom
    int binary_number = 0;
    int mask = 1;
    for (int i = 1; i >= -1; --i) {
        for (int j = 1; j >= -1; --j) {
            // check out of bounds
            if (x + i < 0 || x + i >= image.size() || y + j < 0 || y + j >= image[0].size()) {
                if (lit) {
                    binary_number += mask;
                }
            }
            else if (image[x + i][y + j]) {
                binary_number += mask;
            }
            mask *= 2;
        }
    }
    //std::cout << "\n\nbinary: " << binary_number << std::endl;
    return binary_number;
}

static uint32_t task1(std::string filename) {

    auto input = Input<std::string>(filename);
    
    auto enhance = input[0];

    // bool matrix
    std::vector<std::vector<bool>> image{};

    // init matrix
    for (int i = 1; i < input.size(); i++) {
        std::vector<bool> row{};
        for (int j = 0; j < input[i].size(); j++) {
            row.push_back(input[i][j] == '#');
        }
        image.push_back(row);
    }

    // apply enhance to image
    // add buffer above and below, left and right
    // check square around each pixel

    int steps = 2;

    for (int _ = 0; _ < steps; _++) {
        //std::cout << "step: " << _ + 1 << std::endl;
        // new_image is larger than image
        std::vector<std::vector<bool>> new_image(image.size() + 2, std::vector<bool>(image[0].size() + 2, false));

        for (int i = 0; i < new_image.size(); i++) {
            for (int j = 0; j < new_image[i].size(); j++) {
                    int binary = get_binary_number(image, i - 1, j - 1);
                    new_image[i][j] = enhance[binary] == '#';
            }
        }

        if (enhance[0] == '#') {
            lit = !lit;
        }

        image = new_image;
    }

    // print image
    //for (int i = 0; i < image.size(); i++) {
    //    for (int j = 0; j < image[i].size(); j++) {
    //        std::cout << (image[i][j] ? '#' : '.');
    //    }
    //    std::cout << std::endl;
    //}
    

    // count true in image
    int count = 0;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[i].size(); j++) {
            if (image[i][j]) {
                count++;
            }
        }
    }

    return count;
}

static uint32_t task2(std::string filename) {

    auto input = Input<std::string>(filename);
    
    auto enhance = input[0];

    // bool matrix
    std::vector<std::vector<bool>> image{};

    // init matrix
    for (int i = 1; i < input.size(); i++) {
        std::vector<bool> row{};
        for (int j = 0; j < input[i].size(); j++) {
            row.push_back(input[i][j] == '#');
        }
        image.push_back(row);
    }

    // apply enhance to image
    // add buffer above and below, left and right
    // check square around each pixel

    int steps = 50;

    for (int _ = 0; _ < steps; _++) {
        //std::cout << "step: " << _ + 1 << std::endl;
        // new_image is larger than image
        std::vector<std::vector<bool>> new_image(image.size() + 2, std::vector<bool>(image[0].size() + 2, false));

        for (int i = 0; i < new_image.size(); i++) {
            for (int j = 0; j < new_image[i].size(); j++) {
                    int binary = get_binary_number(image, i - 1, j - 1);
                    //std::cout << enhance[binary] << std::endl;
                    new_image[i][j] = enhance[binary] == '#';
            }
        }

        if (enhance[0] == '#') {
            lit = !lit;
        }

        image = new_image;

        // image to _.ppm
        std::stringstream ss;
        // filename as 3 digit number
        ss << "img_" << std::setfill('0') << std::setw(6) << _ << ".ppm";
        std::ofstream ofs(ss.str());
        ofs << "P3\n" << image.size() << " " << image[0].size() << "\n255\n";
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[i].size(); j++) {
                ofs << (image[i][j] ? "255 255 255 " : "0 0 0 ");
            }
            ofs << "\n";
        }
    }

    // print image
    //for (int i = 0; i < image.size(); i++) {
    //    for (int j = 0; j < image[i].size(); j++) {
    //        std::cout << (image[i][j] ? '#' : '.');
    //    }
    //    std::cout << std::endl;
    //}
    

    // count true in image
    int count = 0;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[i].size(); j++) {
            if (image[i][j]) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    uint32_t test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    uint32_t answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 35) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 3351) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}