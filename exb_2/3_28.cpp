/*
   p44 2-3-28

   用单链表表示集合，分别求集合的交/并/差
  */
#include "common/test_list.h"
using namespace std;

namespace exb_2_3_28 {

typedef ListNode<int> node_t;

node_t * intersect(node_t * a, node_t * b)
{
    if (a == NULL || b == NULL) {
        return NULL;
    }

    node_t head_node;
    node_t * c = &head_node;
    node_t * pa = a;
    node_t * pb = b;

    while (pa != NULL) {
        pb = b;
        while (pb != NULL) {
            if (pb->data == pa->data) {
                break;
            }
            pb = pb->next;
        }
        if (pb != NULL) {
            node_t * n = new node_t;
            n->data = pb->data;
            c->next = n;
            c = n;
        }
        pa = pa->next;
    }

    return head_node.next;
}
node_t * get_union(node_t * a, node_t * b)
{
    node_t * c = NULL;
    node_t * p = a;
    node_t * q = NULL;

    for (; p != NULL; p = p->next) {
        node_t * n = new node_t(p->data);
        n->next = c;
        c = n;
    }

    for (p = b; p != NULL; p = p->next) {
        for (q = a; q != NULL && q->data != p->data; q = q->next)
            ;
        if (q == NULL) {
            node_t * n = new node_t(p->data);
            n->next = c;
            c = n;
        }
    }

    return c;
}
node_t * get_diff(node_t * a, node_t * b)
{
    node_t * c = NULL;
    node_t * pa = NULL;
    node_t * pb = NULL;

    for (pa = a; pa != NULL; pa = pa->next) {
        for (pb = b; pb != NULL && pb->data != pa->data; pb = pb->next)
            ;
        if (pb == NULL) {
            node_t * n = new node_t(pa->data);
            n->next = c;
            c = n;
        }
    }

    return c;
}

CLASS_LIST_RUNNER(int, 2);

void Runner::exec(Lists * obj)
{
    node_t * a = obj->at(0);
    node_t * b = obj->at(1);

    cout << "A: " << a << endl;
    cout << "B: " << b << endl;

    node_t * c_intersect = intersect(a, b);
    cout << "intersect: " << c_intersect << endl;
    node_t * c_union = get_union(a, b);
    cout << "union: " << c_union << endl;
    node_t * c_diff = get_diff(a, b);
    cout << "diff: " << c_diff << endl;

    list_destroy(c_intersect);
    list_destroy(c_union);
    list_destroy(c_diff);
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_3_28

