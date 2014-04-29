#ifndef ARRAY_PTR_H
#define ARRAY_PTR_H

template <typename T>
class array_ptr
{
public:
    explicit array_ptr(T * arr)
        : _arr(arr)
    {}

    ~array_ptr()
    {
        delete[] _arr;
    }

    T & operator[] (int i)
    {
        return *(_arr + i);
    }

    const T & operator[] (int i) const
    {
        return *(_arr + i);
    }

    T * get() const
    {
        return _arr;
    }

    operator T * () const
    {
        return get();
    }

private:
    array_ptr(const array_ptr<T> & a);
    array_ptr<T> & operator= (const array_ptr<T> & a);

private:
    T * _arr;
};

#endif
