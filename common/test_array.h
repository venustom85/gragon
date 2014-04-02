#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H 1

#include <vector>
#include <iostream>

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

};

template <typename E>
std::ostream & operator<< (std::ostream & out, const ArrayObject<E> & a)
{
    return array_print(a.array, a.length);
}

template <typename E>
class SingleArrayRunner : public _Runner< ArrayObject<E> >
{
public:

    ArrayObject<E> * create_object();

    void destroy(ArrayObject<E> * obj);

};

template <typename E>
class MultiArrayRunner : public _Runner< std::vector< ArrayObject<E> > >
{
public:

    typedef std::vector< ArrayObject<E> >  Arrays;

    MultiArrayRunner(int num_arrays)
        : _Runner< std::vector< ArrayObject<E> > > (), _num_arrays(num_arrays)
    {}

    Arrays * create_object();

    void destroy(Arrays * obj);

protected:
    int _num_arrays;
};

template <typename E>
typename MultiArrayRunner<E>::Arrays * MultiArrayRunner<E>::create_object()
{
    Arrays * as = new Arrays;

    for (int c = 0; c < _num_arrays; ++c) {
        int length = 0;
        E * array = array_read<E>(std::cin, length);
        if (array == NULL) {
            delete as;
            return NULL;
        }
        
        as->push_back(ArrayObject<E>(array, length));
    }

    return as;
}

template <typename E>
void MultiArrayRunner<E>::destroy(MultiArrayRunner<E>::Arrays * obj)
{
    for (typename Arrays::iterator i = obj->begin(); i != obj->end(); ++i) {
        delete[] i->array;
    }
    delete obj;
}

template <typename E>
ArrayObject<E> * SingleArrayRunner<E>::create_object()
{
    int length = 0;
    E * array = array_read<E>(std::cin, length);
    if (array == NULL) {
        return NULL;
    }

    return new ArrayObject<E>(array, length);
};

template <typename E>
void SingleArrayRunner<E>::destroy(ArrayObject<E> * obj)
{
    delete[] obj->array;
    delete obj; 
}

#endif

