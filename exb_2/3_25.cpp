/*
   p42 2-3-25

   有一个带头结点的单链表L，其ElemType类型为int，设计一个算法使其元素递增有序。
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_25 {

typedef ListNode<int> node_t;

node_t * sort_ascend(node_t * head)
{
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        return head;
    }

    node_t * sorted_tail = head->next;
    node_t * unsorted_head = sorted_tail->next;
    node_t * f = NULL;

    while (unsorted_head != NULL) {
        f = head;
        while (f->next != unsorted_head && f->next->data < unsorted_head->data) {
            f = f->next;
        }
        if (f->next == unsorted_head) {
            sorted_tail = unsorted_head;
        } else {
            sorted_tail->next = unsorted_head->next;
            unsorted_head->next = f->next;
            f->next = unsorted_head;
        }
        unsorted_head = sorted_tail->next;
    }

    return head;
}

class Runner : public MultiListRunner<int>
{
public:
    Runner()
        : MultiListRunner<int>(1)
    {}

    void exec(Lists * obj)
    {
        node_t * a = obj->at(0);
        a = list_add_head_node(a);
        obj->at(0) = a;

        cout << "Origin list: " << a->next << endl;
        a = sort_ascend(a);
        cout << "Sort ascend: " << a->next << endl;
    }
};

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_25

