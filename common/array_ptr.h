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

    T operator[] (int i) const
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

template <typename T>
class _deleter_base
{
public:
    virtual void del(T * arr) = 0;
};

template <typename T, typename _D>
class _customer_deleter : public _deleter_base<T>
{
public:
    _customer_deleter(_D d) : _d(d) {};

    virtual void del(T * arr)
    {
        _d(arr);
    }

private:
    _D _d;
};

template <typename T>
struct _array_deleter
{
    void operator() (T * arr)
    {
        delete[] arr;
    }
};

template <typename T>
struct _null_deleter
{
    void operator() (T * arr) {}
};

template <typename T>
class _array2d_ptr
{
public:
    class _row_handle
    {
    public:
        _row_handle(T * start)
            : _start(start)
        {}

        T & operator[] (int i)
        {
            return _start[i];
        }

        T operator[] (int i) const
        {
            return _start[i];
        }

    private:
        T * _start;
    };

    class _const_row_handle
    {
    public:
        _const_row_handle(T * start)
            : _start(start)
        {}

        T operator[] (int i)
        {
            return _start[i];
        }

        T operator[] (int i) const
        {
            return _start[i];
        }
    private:
        T * _start;
    };

public:
    template <typename _D>
        _array2d_ptr(T * arr, int col, _D _d)
        : _arr(arr), _col_size(col), _del(new _customer_deleter<T, _D>(_d))
        {}

    ~_array2d_ptr()
    {
        _del->del(_arr);
    }

    int col_size() const
    {
        return _col_size;
    }

    _row_handle operator[] (int i)
    {
        return _row_handle(_arr + i * _col_size);
    }

    _const_row_handle operator[] (int i) const
    {
        return _const_row_handle(_arr + i * _col_size);
    }

private:
    _array2d_ptr(const _array2d_ptr<T> &);
    _array2d_ptr<T> & operator= (const _array2d_ptr<T> &);

private:
    T * _arr;
    int _col_size;
    _deleter_base<T> * _del;
};

template <typename T>
class array2d_ptr : public _array2d_ptr<T>
{
public:
    array2d_ptr(T * arr, int col)
        : _array2d_ptr<T>(arr, col, _array_deleter<T>())
    {}
};

template <typename T>
class array2d_shell : public _array2d_ptr<T>
{
public:
    array2d_shell(T * arr, int col)
        : _array2d_ptr<T>(arr, col, _null_deleter<T>())
    {}
};

#endif
