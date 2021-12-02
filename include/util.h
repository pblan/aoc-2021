#pragma once

#include <string>
#include <vector>
#include <fstream>

inline std::string pass_or_fail(uint32_t answer, uint32_t truth)
{
    return answer == truth ? "PASS" : "FAIL (" + std::to_string(truth) + ")";
}

template <typename T>
struct Input
{
    std::vector<T> raw;
    
    //inline std::vector<std::string> read_file(const std::string& filename)
    Input(const std::string& filename)
    {
        // Read file
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file!");

        // Buffer file
        T buffer;
        while (file >> buffer)
            raw.push_back(buffer);
        file.close();       
    }

    inline size_t size() { return raw.size(); }

    // << operator
    friend std::ostream& operator<<(std::ostream& os, const Input& input)
    {
        for (auto& i : input.raw)
            os << i << " ";
        return os;
    }

    T& operator[](const size_t i) { return raw[i]; }

    auto begin() { return raw.begin(); }
    auto end() { return raw.end(); }

};