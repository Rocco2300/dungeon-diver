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
    CSV(std::string path);
    void load(std::string path);

    bool readLine(std::ifstream& in, std::stringstream& ss);
    std::unordered_map<T, std::string> buildRow(std::stringstream& ss);

    void print();
    std::string operator()(size_t index, T label);
};

template<typename T>
CSV<T>::CSV(std::string path)
{
    load(path);
}

template <typename T>
void CSV<T>::load(std::string path)
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

template <typename T>
std::string CSV<T>::operator()(size_t index, T label)
{
    assert(index >= 0 && index < data.size());
    assert(data[index].find(label) != data[index].end());

    return data[index][label];
}
