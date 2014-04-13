#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>

template <typename T>
class Matrix
{
    typedef Matrix<T> self_t;

public:

    Matrix(int row, int col, const T & t = T());

    ~Matrix();

    int get_row() const { return _row; }
    int get_col() const { return _col; }

    Matrix(const Matrix<T> & m);

    Matrix<T> & operator= (const Matrix<T> & m);

    T & operator() (int row, int col)
    {
        return const_cast<T&>((static_cast<const self_t &>(*this))(row,col));
    }

    const T & operator() (int row, int col) const
    {
        return _array[row * _col + col];
    }

    const T * c_array() const
    {
        return _array;
    }

private:
    void init(const T & t);

private:
    int _row;
    int _col;
    T * _array;
};


// -----------------------------
template <typename T>
std::ostream & matrix_print(const Matrix<T> & m);

template <typename T>
std::ostream & operator<< (std::ostream & out, const Matrix<T> & m);

template <typename T>
std::istream & operator>> (std::istream & in, Matrix<T> & m);

template <typename T>
Matrix<T> * matrix_read(std::istream & in);
// -----------------------------


template <typename T>
Matrix<T>::Matrix(int row, int col, const T & t)
    : _row(row), _col(col), _array(NULL)
{
    init(t);
}

template <typename T>
void Matrix<T>::init(const T & t)
{
    if (_row <= 0 || _col <= 0) {
        throw std::invalid_argument("row and col must be positive");
    }
    _array = new T[ _row * _col ];

    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            (*this)(i,j) = t;
        }
    }
}

template <typename T>
Matrix<T>::~Matrix()
{
    delete[] _array;
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> & m)
    : _row(m._row), _col(m._col), _array(NULL)
{
    init();
    (*this) = m;
}

template <typename T>
Matrix<T> & Matrix<T>::operator= (const Matrix<T> & m)
{
    if (this == &m) {
        return (*this);
    }

    if (_row != m._row || _col != m._col) {
        throw std::invalid_argument("unable to assign matrix with different row or col size");
    }

    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _col; ++j) {
            (*this)(i,j) = m(i,j);
        }
    }

    return (*this);
}

template <typename T>
std::ostream & matrix_print(const Matrix<T> & m)
{
    for (int i = 0; i < m.get_row(); ++i) {
        for (int j = 0; j < m.get_col(); ++j) {
            std::cout << m(i,j) << ' ';
        }
        std::cout << '\n';
    }
    return std::cout;
}

template <typename T>
std::ostream & operator<< (std::ostream & out, const Matrix<T> & m)
{
    return matrix_print(m);
}

template <typename T>
std::istream & operator>> (std::istream & in, Matrix<T> & m)
{
    for (int i = 0; i < m.get_row(); ++i) {
        for (int j = 0; j < m.get_col(); ++j) {
            in >> m(i,j);
        }
    }
    return in;
}

template <typename T>
Matrix<T> * matrix_read(std::istream & in)
{
    int row, col;
    if (!(in >> row >> col)) {
        return NULL;
    }

    try {
        Matrix<T> * pm = new Matrix<T>(row, col);
        in >> (*pm);
        return pm;
    } catch (std::invalid_argument & e) {
        return NULL;
    }
}

#endif
