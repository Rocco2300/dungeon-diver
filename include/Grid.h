#pragma once

#include <cassert>

/** 
 * Custom data class for fixed size 16x16 grid
 * used for custom accessors and logic
 */
template <typename T>
class Grid
{
private:
    T* data;
public:
    Grid();
    ~Grid();

    void alloc();
    void dealloc();

    void fill(T element);

    T& operator[](int index);
    T& operator()(int x, int y);
};

template <typename T>
Grid<T>::Grid() : data{nullptr} { }

template <typename T>
Grid<T>::~Grid()
{
    dealloc();
}

template <typename T>
void Grid<T>::alloc()
{
    data = new T[16 * 16];
}

template <typename T>
void Grid<T>::dealloc()
{
    if (data)
        delete[] data;
}

template <typename T>
void Grid<T>::fill(T element)
{
    assert(data != nullptr);

    for (int i = 0; i < 16 * 16; i++)
    {
        data[i] = element;
    }
}

template <typename T>
T& Grid<T>::operator[](int index)
{
    assert(index >= 0 && index < 16 * 16);

    return data[index];
}

template <typename T>
T& Grid<T>::operator()(int x, int y)
{
    assert(x >= 0 && x < 16 * 16 && y >= 0 && y < 16 * 16);

    return data[y * 16 + x];
}