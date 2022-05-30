#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>
#include <cassert>

template <typename T>
class CSV
{
private:
    std::vector<std::unordered_map<T, std::string>> data;

public:
    CSV() = default;
    CSV(const char* path);
    void load(const char* path);

    bool readLine(std::ifstream& in, std::stringstream& ss);
    std::unordered_map<T, std::string> buildRow(std::stringstream& ss);

    void print();
};

template<typename T>
CSV<T>::CSV(const char* path)
{
    load(path);
}

template <typename T>
void CSV<T>::load(const char* path)
{
    std::ifstream in(path);
    std::stringstream ss;

    // Skip the table head
    readLine(in, ss);
    ss.str("");

    while (readLine(in, ss))
    {
        std::unordered_map<T, std::string> row = buildRow(ss);
        data.push_back(row);
    }

    in.close();
}

template <typename T>
bool CSV<T>::readLine(std::ifstream& in, std::stringstream& ss)
{
    ss.clear();

    std::string line;

    if (!std::getline(in, line))
        return false;   
    
    ss << line;

    return true;
}

template <typename T>
std::unordered_map<T, std::string> CSV<T>::buildRow(std::stringstream& ss)
{
    int cnt = 0;

    std::string token;
    std::unordered_map<T, std::string> row;

    while (std::getline(ss, token, ','))
    {
        row[(T)cnt] = token;
        cnt++;
    }

    return row;
}

template <typename T>
void CSV<T>::print()
{
    for (size_t i = 0; i < data.size(); i++)
    {
        for (const auto& [fieldName, value] : data[i])
        {
            std::cout << (int)fieldName << " " << value << " | ";
        }

        std::cout << "\n";
    }
}
