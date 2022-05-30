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

    bool readLine(std::ifstream& in, std::stringstream& ss);
    std::unordered_map<T, std::string> buildRow(std::stringstream& ss);

    void print();
};

template<typename T>
CSV<T>::CSV(const char* path)
{
    std::ifstream in(path);
    std::stringstream ss;

    // Skip the table head
    readLine(in, ss);
    ss.str("");

    std::cout << ss.str() << std::endl;

    while (readLine(in, ss))
    {
        std::cout << ss.str() << std::endl;

        std::unordered_map<T, std::string> row = buildRow(ss);
        data.push_back(row);
    }
    // std::unordered_map<T, std::string> header;
    // std::unordered_map<T, std::string> entry;

    // readLine(in, header);

    // bool first = true;
    // // char line[256];
    // std::string line;
    // std::stringstream ss;
    // while (std::getline(in, line))
    // {
    //     if (first)
    //     {
    //         first = false;
    //         continue;   
    //     }

    //     int cnt = 0;
    //     ss << line;
    //     std::string token;
    //     std::unordered_map<T, std::string> entry;
    //     while (std::getline(ss, token, ','))
    //     {
    //         entry[(T)cnt] = token;
    //         cnt++;
    //     }

    //     data.push_back(entry);
    // }

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
