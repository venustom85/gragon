/*
   Reverse a list, including recursively.
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_list_rev {

typedef ListNode<int> node_t;

node_t * reverse(node_t * h)
{
    node_t * new_head = NULL;
    node_t * t = NULL;
    while (h != NULL) {
        t = h;
        h = h->next;
        t->next = new_head;
        new_head = t;
    }
    return new_head;
}

node_t * reverse_2(node_t * h)
{
    if (h == NULL) {
        return NULL;
    }

    node_t * last = NULL;
    node_t * next = NULL;
    while (h != NULL) {
        next = h->next;
        h->next = last;
        last = h;
        h = next;
    }
    return last;
}

node_t * reverse_recursively(node_t * h)
{
    if (h == NULL || h->next == NULL) {
        return h;
    }

    node_t * rev_head = reverse_recursively(h->next);
    h->next->next = h;
    h->next = NULL;
    return rev_head;
}

CLASS_LIST_RUNNER(int, 1);

void Runner::exec(Lists * obj)
{
    node_t * h = obj->at(0);
    cout << "Origin list: " << h << endl;

    node_t * a = list_clone(h);
    a = reverse_2(a);
    cout << "Reverse: " << a << endl;

    node_t * b = list_clone(h);
    b = reverse_recursively(b);
    cout << "Reverse recursively: " << b << endl;

    list_destroy(a);
    list_destroy(b);
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_list_rev

