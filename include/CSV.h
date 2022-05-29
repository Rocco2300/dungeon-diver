#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>

template <typename T>
class CSV
{
private:
    std::vector<std::unordered_map<T, std::string>> data;

public:
    CSV() = default;
    CSV(const char* path);

    void print();
};

template<typename T>
CSV<T>::CSV(const char* path)
{
    // std::assert(std::is_enum(T));

    std::ifstream in(path);

    bool first = true;
    // char line[256];
    std::string line;
    std::stringstream ss;
    while (std::getline(in, line))
    {
        if (first)
        {
            first = false;
            continue;   
        }

        int cnt = 0;
        ss << line;
        std::string token;
        std::unordered_map<T, std::string> entry;
        while (std::getline(ss, token, ','))
        {
            entry[(T)cnt] = token;
            cnt++;
        }

        data.push_back(entry);
    }
}

template <typename T>
void CSV<T>::print()
{
    for (size_t i = 0; i < data.size(); i++)
    {
        for (const auto& [fieldName, value] : data[i])
        {
            std::cout << " | " << (int)fieldName << " " << value;
        }

        std::cout << "|\n";
    }
}
