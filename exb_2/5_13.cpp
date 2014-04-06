/*
   p64 2-5-13(改)

   倒置一个以尾指针表示的循环单链表。
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_5_13 {

typedef ListNode<int> node_t;

node_t * reverse_circular(node_t * rear)
{
    if (rear == NULL) {
        return NULL;
    }

    node_t * head = rear->next;
    node_t * h = NULL;
    node_t * p = rear;
    node_t * t = NULL;

    while (p->next != rear) {
        t = p;
        p = p->next;
        t->next = h;
        h = t;
    }

    p->next = h;

    rear->next = p;

    return head;
}

CLASS_LIST_RUNNER(int, 1);

void Runner::exec(Lists * obj)
{
    node_t * a = obj->at(0);
    a = list_clone(a);
    node_t * rear = list_to_circular(a);
    cout << "Original circular list: ";
    list_print_circular(rear) << endl;

    rear = reverse_circular(rear);
    cout << "Reversed: ";
    list_print_circular(rear) << endl;

    list_destroy_circular(rear);
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_5_13

