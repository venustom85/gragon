#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <new>
#include <cstdio>

#include "base.h"

template <typename T> std::ostream & array_print(const T * begin, const T * end);
template <typename T> std::ostream & array_println(const T * begin, const T * end);
template <typename T> std::ostream & array_print(const T * arr, int length);
template <typename T> std::ostream & array_println(const T * arr, int length);
template <typename T> T * array_read(std::istream & in, int & length);
template <typename T> T * array_read_from_file(const char * filename, int & length);
template <typename T> void array_destroy(T * arr);
template <typename T> T * array_expand(T * arr, int length);

template <typename T>
std::ostream & array_print(const T *begin, const T *end)
{
    std::cout << '[';
    while (begin < end) {
        std::cout << *begin++ << ' ';
    }
    return std::cout << ']';
}

template <typename T>
std::ostream & array_println(const T *begin, const T *end)
{
    return array_print(begin, end) << '\n';
}

template <typename T>
std::ostream & array_print(const T *arr, int length)
{
    return array_print(arr, arr + length);
}

template <typename T>
std::ostream & array_println(const T *arr, int length)
{
    return array_print(arr, length) << '\n';
}

template <typename T>
T * array_read(std::istream &in, int &length)
{
    in >> length;
    if (!in) {
        gragon::set_error_message("NO length of array found in stream");
        return NULL;
    }

    if (length < 0) {
        sprintf(gragon::get_error_buf(), "ERROR length of array: %d", length);
        return NULL;
    }

    T * array = NULL;
    try {
        array = new T[length];
    } catch (std::bad_alloc & e) {
        gragon::set_error_message("FAILED to allocate");
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        in >> array[i];
        if (!in) {
            sprintf(gragon::get_error_buf(), "UNABLE to read element[%d]", i);
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

template <typename T> 
T * array_expand(T * arr, int length)
{
    if (length < 0) {
        return NULL;
    }

    int new_len = length > 0 ? length * 2 : 1;

    T * new_arr = new T[new_len];
    for (int i = 0; i < length; ++i) {
        new_arr[i] = arr[i];
    }

    array_destroy(arr);

    return new_arr;
}

#endif
