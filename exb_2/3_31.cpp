/*
   p46 2-3-31

   已知递增有序的单链表A、B和C分别存储了一个集合，设计一个算法实现A＝AV(B^C)，并使求解结果A仍保持递增。要求算法的时间复杂度为O(|A|+|B|+|C|)。其中|A|为集合A的元素个数。
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_31 {

typedef ListNode<int> node_t;

node_t * get_intersect(node_t * b, node_t * c)
{
    node_t head;
    node_t * h = &head;

    while (b != NULL && c != NULL) {
        if (b->data < c->data) {
            b = b->next;
        } else if (c->data < b->data) {
            c = c->next;
        } else {
            node_t * n = new node_t(b->data);
            h->next = n;
            h = n;
            b = b->next;
            c = c->next;
        }
    }

    return head.next;
}

node_t * get_union(node_t * a, node_t * b)
{
    node_t head;
    head.next = a;
    node_t * pa = &head;
    node_t * pb = b;
    node_t * n = NULL;
    while (pa->next != NULL && pb != NULL) {
        if (pa->next->data > pb->data) {
            n = pb;
            pb = pb->next;
            n->next = pa->next;
            pa->next = n;
        } else if (pa->next->data == pb->data) {
            n = pb;
            pb = pb->next;
            delete n;
        }
        pa = pa->next;
    }

    if (pb != NULL) {
        pa->next = pb;
    }

    return head.next;
}

node_t * proc(node_t * a, node_t * b, node_t * c)
{
    return get_union(a, get_intersect(b, c));
}

CLASS_LIST_RUNNER(int, 3);

void Runner::exec(Lists * obj)
{
    node_t * a = obj->at(0);
    node_t * b = obj->at(1);
    node_t * c = obj->at(2);
    
    cout << "A: " << a << endl;
    cout << "B: " << b << endl;
    cout << "C: " << c << endl;
    a = proc(a, b, c);
    cout << "New A: " << a << endl;

    obj->at(0) = a;
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_31

