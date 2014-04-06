/*
   p65 2-5-15

   一个含有两个以上（包括两个）结点的循环双链表，将第一个元素值为x的结点与其后继结点交换。
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_5_15 {

typedef ListNode<int> node_t;

void swap_node(node_t * a, node_t * b)
{
    node_t * m = a->prev;
    node_t * n = b->next;
    
    m->next = b;
    b->prev = m;

    b->next = a;
    a->prev = b;

    a->next = n;
    n->prev = a;
}

node_t * exchange_first_x_and_next(node_t * rear, int x)
{
    if (rear == NULL || rear->next == rear) {
        return rear;
    }

    node_t * p = rear->next;
    while (p != rear && p->data != x) {
        p = p->next;
    }

    if (p->data != x) {
        return rear;
    }

    if (p->next->next == p) {
        rear = rear->prev;
        return rear;
    }

    if (p->next == rear) {
        swap_node(p, rear);
        node_t * temp = p;
        p = rear;
        rear = temp;
    } else if (p == rear) {
        node_t * next = rear->next;
        swap_node(rear, next);
        node_t * temp = rear;
        rear = next;
        next = temp;
    } else {
        swap_node(p, p->next);
    }

    return rear;
}

CLASS_LIST_RUNNER(int, 1);

void Runner::exec(Lists * obj)
{
    node_t * a = obj->at(0);
    a = list_clone(a);
    node_t * rear = list_to_circular(a);

    cout << "Original circular list: ";
    list_print_circular(rear) << endl;

    rear = exchange_first_x_and_next(rear, 0);
    cout << "swap first '0' and next: ";
    list_print_circular(rear) << endl;

    list_destroy_circular(rear);
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_5_15

