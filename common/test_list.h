#ifndef TEST_LIST_H
#define TEST_LIST_H 1

#include <vector>

#include "test.h"
#include "list.h"

template <typename E>
class MultiListRunner : public _Runner< std::vector<ListNode<E>*> >
{
public:

    typedef std::vector<ListNode<E>*> Lists;

    MultiListRunner(int num_list)
        : _Runner<Lists>(), _num_list(num_list)
    {}

    Lists * create_object();

    void destroy(Lists * obj);

private:
    int _num_list;
};

#define CLASS_LIST_RUNNER(type,n) \
class Runner : public MultiListRunner<type> \
{ \
public: \
    Runner() : MultiListRunner<type>(n) {} \
    void exec(Lists * obj); \
}; 

template <typename E>
typename MultiListRunner<E>::Lists * MultiListRunner<E>::create_object()
{
    Lists * ls = new Lists;

    for (int i = 0; i < _num_list; ++i) {
        int length;
        ListNode<E> * L = list_read<E>(std::cin, length);
        if (L == NULL && length < 0) {
            delete ls;
            return NULL;
        }
        ls->push_back(L);
    }

    return ls;
}

template <typename E>
void MultiListRunner<E>::destroy(Lists * obj)
{
    for (typename Lists::iterator i = obj->begin(); i != obj->end(); ++i) {
        list_destroy(*i);
    }
    delete obj;
}

#endif

