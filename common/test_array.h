#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H 1

#include "test.h"
#include "array.h"

template <typename E>
struct ArrayObject
{
    E * array;
    int length;

    ArrayObject() : array(NULL), length(0) {}

    ArrayObject(E * arr, int len)
        : array(arr), length(len) {}

    ~ArrayObject()
    {
        delete[] array;
        array = NULL;
        length = 0;
    }

};

template <typename E>
class SingleArrayRunner : public FileRunner< ArrayObject<E> >
{
public:

    ArrayObject<E> * create_object();

    void destroy(ArrayObject<E> * obj);

};

template <typename E>
ArrayObject<E> * SingleArrayRunner<E>::create_object()
{
    int length = 0;
    E * array = array_read(this->_fin, length);
    if (array == NULL) {
        return NULL;
    }

    return new ArrayObject<E>(array, length);
};

template <typename E>
void SingleArrayRunner<E>::destroy(ArrayObject<E> * obj)
{
    delete obj; 
}

#endif

