#pragma once

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

    void fill(int);
    void clear();

    T& operator[](int index);
    T& operator()(int x, int y);
};
