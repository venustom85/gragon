/*
   p66 2-5-16(改)

   倒置一个循环双链表
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_5_16 {

typedef ListNode<int> node_t;

node_t * reverse_circular(node_t * rear)
{
    if (rear == NULL || rear->next == rear) {
        return rear;
    }

    if (rear->next->next == rear) {
        return rear->next;
    }

    node_t * p = rear;
    node_t * q = NULL;

    do {
        q = p->next;
        p->next = p->prev;
        p->prev = q;
        p = q;
    } while (p != rear);

    return rear->prev;
}

CLASS_LIST_RUNNER(int,1);

void Runner::exec(Lists * obj)
{
    node_t * a = obj->at(0);
    a = list_clone(a);
    node_t * rear = list_to_circular(a);

    cout << "Original circular list: ";
    list_print_circular(rear) << endl;

    rear = reverse_circular(rear);
    cout << "Reverse: ";
    list_print_circular(rear) << endl;

    list_destroy_circular(rear);
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_5_16

