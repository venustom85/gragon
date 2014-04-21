/*
   p229 7-3-43

   将二叉树表示的四则算术表达式按中缀表达式输出。
  */
#include <cctype>
#include "common/bi_tree.h"
using namespace std;

namespace exb_7_3_43 {

typedef BiNode<char> node_t;

void print_expr(node_t * root)
{
    if (root == NULL) {
        return;
    }

    char c = root->data;
    if ((c == '*' || c == '/') && root->lc != NULL && (root->lc->data == '+' || root->lc->data == '-')) {
        cout << "(";
        print_expr(root->lc);
        cout << ")";
    } else if (root->lc != NULL) {
        print_expr(root->lc);
    }

    cout << c;

    if (root->rc != NULL) {
        if (c == '*' && (root->rc->data == '+' || root->rc->data == '-') || c == '-' && (root->rc->data == '+' || root->rc->data == '-') || c == '/' && !isdigit(root->rc->data)) {
            cout << "(";
            print_expr(root->rc);
            cout << ")";
        } else {
            print_expr(root->rc);
        }
    }
}

int g_main(int argc, char ** argv)
{
    node_t * root = NULL;
    while ((root = bitree_read<char>(cin)) != NULL) {
        cout << bitree_io(root) << endl;
        print_expr(root);
        cout << endl;
        cout << "===============================" << endl;
        bitree_destroy(root);
    }
    return 0;
}

} // namespace exb_7_3_43

