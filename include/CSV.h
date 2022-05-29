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
