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
    
    // 1 - 10
    int pos1 = std::stoi(input[4]);
    int pos2 = std::stoi(input[9]);

    std::cout << "pos1: " << pos1 << std::endl;
    std::cout << "pos2: " << pos2 << std::endl;

    std::pair<int, int> scores{0, 0};
    
    int die_sum{6}, rolls{0};

    // while true
    while (true) {
        pos1 += die_sum; 
        pos1 = pos1 % 10; 
        rolls += 3; 

        scores.first += (pos1 == 0 ? 10 : pos1);
        if (scores.first >= 1000) {
            return scores.second * rolls;
        }
        die_sum += 9;

        pos2 += die_sum;
        pos2 = pos2 % 10;
        rolls += 3;

        scores.second += (pos2 == 0 ? 10 : pos2);
        if (scores.second >= 1000) {
            return scores.first * rolls;
        }
        die_sum += 9;
    }

    return -1;
}

// p(0) = 0
// p(1) = 0
// p(2) = 0
// p(3) = 1
// p(4) = 3
// p(5) = 6
// p(6) = 7
// p(7) = 6
// p(8) = 3
// p(9) = 1
int OUTCOME_COUNT[10] = {0,0,0,1,3,6,7,6,3,1};

static void dirac(int pos1, int pos2, int score1, int score2, long long& win1, long long& win2, long long turns, bool turn) {
    // if turn is odd then player 1
    if (turn) {
        // split for each possible outcome
        for (int i = 3; i <= 9; i++) {
            int npos1 = (pos1 + i) % 10;
            npos1 = (npos1 == 0 ? 10 : npos1);
            int nscore1 = score1 + npos1;

            // this happen OUTCOME_COUNT[i] times
            if (nscore1 >= 21) {
                win1 += turns * OUTCOME_COUNT[i];
            }
            else {
                // split OUTCOME_COUNT[i] times
                dirac(npos1, pos2, nscore1, score2, win1, win2, turns * OUTCOME_COUNT[i], !turn);
            }
        }
    } else {
        for (int i = 3; i <= 9; i++) {
            int npos2 = (pos2 + i) % 10;
            npos2 = (npos2 == 0 ? 10 : npos2);
            int nscore2 = score2 + npos2;

            if (nscore2 >= 21) {
                win2 += turns * OUTCOME_COUNT[i];
            }
            else {
                dirac(pos1, npos2, score1, nscore2, win1, win2, turns * OUTCOME_COUNT[i], !turn);
            }
        }
    }
}

static long long task2(std::string filename) {

    auto input = Input<std::string>(filename);
    
    // 1 - 10
    int pos1 = std::stoi(input[4]);
    int pos2 = std::stoi(input[9]);

    std::cout << "pos1: " << pos1 << std::endl;
    std::cout << "pos2: " << pos2 << std::endl;
    
    long long win1{0}, win2{0};

    // use BFS in dirac
    dirac(pos1, pos2, 0, 0, win1, win2, 1, true);

    std::cout << "win1: " << win1 << std::endl;
    std::cout << "win2: " << win2 << std::endl;

    // return bigger one
    return std::max(win1, win2);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t test_answer1{task1("test_input.txt")};
    long long test_answer2{task2("test_input.txt")};

    uint32_t answer1{task1("input.txt")};
    long long answer2{task2("input.txt")};
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 739785) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 444356092776315) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}