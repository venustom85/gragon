/*
   p65 2-5-14(改)

   删除循环双链表中第一个值为x的结点
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_5_14 {

typedef ListNode<int> node_t;

node_t * remove_first_x(node_t * rear, int x)
{
    if (rear == NULL) {
        return NULL;
    }

    node_t * p = rear->next;
    while (p != rear && p->data != x) {
        p = p->next;
    }

    if (p->data != x) {
        return rear;
    }

    if (p == rear) {
        if (rear->next == rear) {
            delete p;
            return NULL;
        } else {
            rear = rear->prev;
        }
    }

    p->next->prev = p->prev;
    p->prev->next = p->next;
    delete p;

    return rear;
}

CLASS_LIST_RUNNER(int, 1);

void Runner::exec(Lists * obj)
{
    node_t * a = obj->at(0);
    a = list_clone(a);
    node_t * rear = list_to_circular(a);

    cout << "Original List: ";
    list_print_circular(rear) << endl;

    rear = remove_first_x(rear, 0);
    cout << "Remove first '0': ";
    list_print_circular(rear) << endl;

    list_destroy_circular(rear);
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_5_14

