#pragma once

#include <cassert>

template <typename Grid>
class GridIterator
{
public:
    using ValueType = typename Grid::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
private:
    PointerType ptr;
public:
    GridIterator(PointerType ptr) : ptr{ptr} {}

    GridIterator& operator++()
    {
        ptr++;
        return *this;
    }

    GridIterator& operator++(int)
    {
        auto iterator = *this;
        ++(*this);
        return iterator;
    }

    GridIterator& operator--()
    {
        ptr--;
        return *this;
    }

    GridIterator& operator--(int)
    {
        auto iterator = *this;
        --(*this);
        return iterator;
    }

    ReferenceType operator[](int index)
    {
        return *(ptr + index);
    }

    PointerType operator->()
    {
        return ptr;
    }

    ReferenceType operator*()
    {
        return *ptr;
    }

    bool operator==(const GridIterator& other)
    {
        return ptr == other.ptr;
    }

    bool operator!=(const GridIterator& other)
    {
        return ptr != other.ptr;
    }
};

/** 
 * Custom data class for fixed size 16x16 grid
 * used for custom accessors and logic
 */
template <typename T>
class Grid
{
public:
    using ValueType = T;
    using Iterator = GridIterator<Grid<T>>;
private:
    T* data;
public:
    Grid() : data{nullptr} { }

    ~Grid()
    {
        dealloc();
    }

    void alloc()
    {
        data = new T[16 * 16];
    }

    void dealloc()
    {
        if (data != nullptr)
            delete[] data;
    }

    void fill(T element)
    {
        assert(data != nullptr);

        for (int i = 0; i < 16 * 16; i++)
        {
            data[i] = element;
        }
    }

    T& operator[](int index)
    {
        assert(data != nullptr);
        assert(index >= 0 && index < 16 * 16);

        return data[index];
    }
    
    T& operator()(int x, int y)
    {
        assert(data != nullptr);
        assert(x >= 0 && x < 16 * 16 && y >= 0 && y < 16 * 16);

        return data[y * 16 + x];
    }


    Iterator begin()
    {
        return Iterator(data);
    }

    Iterator end()
    {
        return Iterator(data + (16 * 16));
    }
};

