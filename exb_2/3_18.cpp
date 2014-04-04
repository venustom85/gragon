/*
   p39 2-3-18

   设C={a1,b2,a2,b2,...,an,bn}为一线性表，采用带头结点的hc单链表存放，设计一个就地算法，将其拆分为两个线性表，使得A={a1,a2,...,an}，B={b1,b2,...,bn}。
   */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_18 {

typedef ListNode<int> node_t;

// head - list a
// return list b, with a head node
node_t * split(node_t * head)
{
    node_t * b = new node_t;

    if (head == NULL) {
        return b;
    }

    node_t * pa = head->next;
    node_t * pb = b;

    while (pa != NULL) {
        node_t * pa_next = pa->next;
        if (pa_next != NULL) {
            pa->next = pa_next->next;
            pb->next = pa_next;
            pb = pa_next;
        }
        pa = pa->next;
    }

    pb->next = NULL;

    return b;
}

class Runner : public MultiListRunner<int>
{
public:
    Runner()
        : MultiListRunner<int>(1)
    {}

    void exec(Lists * obj)
    {
        node_t * head = obj->at(0);
        head = list_add_head_node(head);

        cout << "Origin list: " << head->next << endl;

        node_t * b = split(head);
        cout << "A: " << head->next << endl;
        cout << "B: " << b->next << endl;

        delete head;
        list_destroy(b);
    }
};

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_18
