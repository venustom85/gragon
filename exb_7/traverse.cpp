/*
   非递归实现二叉树的先中后序遍历
  */
#include <stack>
#include "common/bi_tree.h"
using namespace std;

namespace exb_7_traverse {

typedef BiNode<char> node_t;

struct frame
{
    const node_t * root;
    int step;
};

void pre_order_print(const node_t * root)
{
    frame F;
    stack<frame> stk;

    F.step = 0;
    F.root = root;
    stk.push(F);

    while (!stk.empty()) {
        frame & t = stk.top();
        if (t.step == 0) {
            if (t.root == NULL) {
                stk.pop();
            } else {
                cout << t.root->data << ' ';
                t.step = 1;
                F.root = t.root->lc;
                stk.push(F);
            }
        } else if (t.step == 1) {
            t.step = 2;
            F.root = t.root->rc;
            stk.push(F);
        } else {
            stk.pop();
        }
    }

    cout << endl;
}

void in_order_print(const node_t * root)
{
    frame F;
    stack<frame> stk;

    F.step = 0;
    F.root = root;
    stk.push(F);

    while (!stk.empty()) {
        frame & t = stk.top();
        if (t.step == 0) {
            if (t.root == NULL) {
                stk.pop();
            } else {
                t.step = 1;
                F.root = t.root->lc;
                stk.push(F);
            }
        } else if (t.step == 1) {
            cout << t.root->data << ' ';
            t.step = 2;
            F.root = t.root->rc;
            stk.push(F);
        } else {
            stk.pop();
        }
    }

    cout << endl;
}

void post_order_print(const node_t * root)
{
    frame F;
    stack<frame> stk;

    F.step = 0;
    F.root = root;
    stk.push(F);

    while (!stk.empty()) {
        frame & t = stk.top();
        if (t.step == 0) {
            if (t.root == NULL) {
                stk.pop();
            } else {
                t.step = 1;
                F.root = t.root->lc;
                stk.push(F);
            }
        } else if (t.step == 1) {
            t.step = 2;
            F.root = t.root->rc;
            stk.push(F);
        } else {
            cout << t.root->data << ' ';
            stk.pop();
        }
    }

    cout << endl;
}

int g_main(int argc, char ** argv)
{
    node_t * root = NULL;
    while ((root = bitree_read<char>(cin)) != NULL) {
        cout << "original tree: ";
        bitree_print(cout, root) << endl;
        cout << "pre order print: ";
        pre_order_print(root);
        cout << "in order print: ";
        in_order_print(root);
        cout << "post order print: ";
        post_order_print(root);
        cout << "===============================" << endl;
        bitree_destroy(root);
    }
    return 0;
}

} // namespace exb_7_traverse

