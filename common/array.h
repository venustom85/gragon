#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <new>

template <typename T>
std::ostream & array_print(const T *begin, const T *end)
{
    while (begin < end) {
        std::cout << *begin++ << ' ';
    }
    return std::cout;
}

template <typename T>
std::ostream & array_print(const T *arr, int length)
{
    return array_print(arr, arr + length);
}

template <typename T>
T * array_read(std::istream &in, int &length)
{
    in >> length;
    if (!in) {
        std::cerr << "NO length of array found in stream\n";
        return NULL;
    }

    if (length <= 0) {
        std::cerr << "ERROR length of array: " << length << '\n';
        return NULL;
    }

    T * array = NULL;
    try {
        array = new T[length];
    } catch (std::bad_alloc & e) {
        std::cerr << "FAILED to allocate\n";
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        in >> array[i];
        if (!in) {
            std::cerr << "UNABLE to read element[" << i << "]\n";
            array_destroy(array);
            return NULL;
        }
    }

    return array;
}

template <typename T>
T * array_read_from_file(const char *filename, int &length)
{
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "FAILED to open file " << filename << '\n';
        return NULL;
    }

    return array_read<T>(fin, length);
}

template <typename T>
void array_destroy(T * arr)
{
    delete[] arr;
}

#endif
