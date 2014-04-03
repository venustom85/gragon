#ifndef TEST_LIST_H
#define TEST_LIST_H 1

#include <vector>

#include "test.h"
#include "array.h"

template <typename E>
class MultiListRunner : public _Runner< std::vector<ListNode*> >
{
public:

    typedef std::vector<ListNode*> Lists;

    MultiListRunner(int num_list)
        : _Runner<Lists>(), _num_list(num_list)
    {}

    Lists * create_object();

    void destroy(Lists * obj);

private:
    int _num_list;
};

template <typename E>
typename MultiListRunner<E>::Lists * MultiListRunner<E>::create_object()
{
    Lists * ls = new Lists;

    for (int i = 0; i < _num_list; ++i) {
        ListNode<E> * L = list_read<E>(std::in);
        if (L == NULL) {
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

