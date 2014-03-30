#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <typename T>
void array_print(const T *begin, const T *end)
{
    while (begin != end) {
        std::cout << *begin++ << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void array_print(const T *arr, int length)
{
    array_print(arr, arr + length);
}

#endif
