/*
   p49 2-3-35

   已知3个单链表ABC中的结点均依元素值自小至大非递减排列（可能存在两个以上值相同的结点），设计一个算法使链表A中仅留下3个表中均包含的数据元素结点，且没有值相同的结点，并释放所有无用结点。限定算法时间复杂度为O(m+n+p)。
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_35 {

typedef ListNode<int> node_t;

node_t * keep_same(node_t * & a, node_t * & b)
{
    node_t ah;
    node_t * pa = &ah;
    ah.next = a;

    node_t bh;
    node_t * pb = &bh;
    bh.next = b;

    node_t * t = NULL;

    while (pa->next != NULL && pb->next != NULL) {
        if (pa->next->data < pb->next->data) {
            t = pa->next;
            pa->next = t->next;
            delete t;
        } else if (pa->next->data > pb->next->data) {
            t = pb->next;
            pb->next = t->next;
            delete t;
        } else {
            t = pb->next;
            pb->next = t->next;
            delete t;

            pa = pa->next;
            while (pa->next != NULL && pa->next->data == pa->data) {
                t = pa->next;
                pa->next = t->next;
                delete t;
            }
        }
    }

    while (pa->next != NULL) {
        t = pa->next;
        pa->next = t->next;
        delete t;
    }

    while (pb->next != NULL) {
        t = pb->next;
        pb->next = t->next;
        delete t;
    }

    b = NULL;
    a = ah.next;

    return a;
}

node_t * keep_same(node_t * & a, node_t * & b, node_t * & c)
{
    a = keep_same(a, b);
    return keep_same(a, c);
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

    a = keep_same(a, b, c);
    cout << "After: " << a << endl;

    obj->at(0) = a;
    obj->at(1) = b;
    obj->at(2) = c;
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_35

