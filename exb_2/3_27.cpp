/*
   p43 2-3-27

   有一个线性表，采用带头结点的单链表L存储，设计一个算法将其就地逆置。所谓“就地”指辅助空间应为O(1)。
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_27 {

typedef ListNode<int> node_t;

node_t * reverse(node_t * head)
{
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        return head;
    }

    node_t * new_head = NULL;
    node_t * old_head = head->next;
    node_t * help = NULL;

    while (old_head != NULL) {
        help = old_head;
        old_head = old_head->next;
        help->next = new_head;
        new_head = help;
    }

    head->next = new_head;

    return head;
}

CLASS_LIST_RUNNER(int,1);

void Runner::exec(Lists * obj)
{
    node_t * a = obj->at(0);
    a = list_add_head_node(a);
    obj->at(0) = a;

    cout << "Origin list: " << a->next << endl;
    a = reverse(a);
    cout << "Reverse list: " << a->next << endl;
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_27

