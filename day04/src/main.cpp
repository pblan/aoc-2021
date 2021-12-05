#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include <util.h>


std::vector<int> draw;

bool won(const bool board[25]) {
    for (int i = 0; i < 5; ++i) 
        // check horizontal
        if (board[i * 5] && board[i * 5 + 1] && board[i * 5 + 2] && board[i * 5 + 3] && board[i * 5 + 4]) // alter copilot du geile sau
            return true;
    
    for (int i = 0; i < 5; ++i) 
        // check vertical
        if (board[i] && board[1 * 5 + i] && board[2 * 5 + i] && board[3 * 5 + i] && board[4 * 5 + i])
            return true;
    
    return false;
}

int calc_rounds(const int board[25]) {
    bool board_temp[25]{}; // inits with 0s

    // for each drawn number ...
    for (size_t i = 0; i < draw.size(); ++i) {
        // ... for each position ...
        for (int j = 0; j < 25; ++j) {
            // ... if the number is drawn at that position ...
            if (board[j] == draw[i]) {
                // ... mark it as drawn
                board_temp[j] = true;
                break;
            }

            // check if we won
            if (won(board_temp))
                return i;
        }
    }

    return -1;
}

int answer(const int board[25], int rounds) {
    bool board_temp[25]{}; // inits with 0s
    int sum{};

    for (int i = 0; i < rounds; ++i)
        for (int j = 0; j < 25; ++j)
            if (board[j] == draw[i])
                board_temp[j] = true;
    
    for (int i = 0; i < 25; ++i)
        if (!board_temp[i])
            sum += board[i];

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Rounds: " << rounds << std::endl;
    std::cout << "Draw: " << draw[rounds - 1] << std::endl;

    std::cout << "Result: " << sum * draw[rounds - 1] << "\n" << std::endl;

    return sum * draw[rounds - 1];
}

static std::tuple<int, int> task(std::string filename) {

    auto input = Input<std::string>(filename);

    // clear draw
    draw.clear();

    // init draw order
    std::stringstream ss(input[0]);
    std::string token;
    while (std::getline(ss, token, ',')) {
        draw.push_back(std::stoi(token));
    }

    int board[25], board_min[25], board_max[25];
    int rounds, min_rounds = 1337, max_rounds = 0; // max rounds is 2^32 - 1

    // offset for input
    int pos{1};

    for(size_t i=0; i < (input.size() - 1) / 25; ++i)
    {   
        // filling the board
        for (int &j : board) {
            j = std::stoi(input[pos]);
            pos++;
        }

        rounds = calc_rounds(board);

        // thanks copilot
        if (rounds < min_rounds) {
            min_rounds = rounds;
            for (int i = 0; i < 25; ++i)
                board_min[i] = board[i];
        }

        if (rounds > max_rounds) {
            max_rounds = rounds;
            for (int i = 0; i < 25; ++i)
                board_max[i] = board[i];
        }
    }

    return {answer(board_min, min_rounds), answer(board_max, max_rounds)};
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    auto [test_answer1, test_answer2] = task("test_input.txt");

    auto [answer1, answer2] = task("input.txt");
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " μs" << std::endl;

    std::cout << "[Test] Task 1: " << test_answer1 << " " << pass_or_fail(test_answer1, 4512) << std::endl;
    std::cout << "[Test] Task 2: " << test_answer2 << " " << pass_or_fail(test_answer2, 1924) << std::endl;


    std::cout << "Task 1: " << answer1 << std::endl;
    std::cout << "Task 2: " << answer2 << std::endl;
}