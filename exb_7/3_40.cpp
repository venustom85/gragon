/*
   将二叉树逆时针旋转90度打印出来
  */
#include "common/bi_tree.h"
using namespace std;

namespace exb_7_3_40 {

typedef BiNode<char> node_t;

void rotate_print_impl(node_t * root, int level)
{
    if (root == NULL) {
        return;
    }

    rotate_print_impl(root->rc, level + 1);
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }
    cout << root->data << endl;
    rotate_print_impl(root->lc, level + 1);
}

void rotate_print(node_t * root)
{
    rotate_print_impl(root, 0);
}

int g_main(int argc, char ** argv)
{
    node_t * root = NULL;
    while ((root = bitree_read<char>(cin)) != NULL) {
        cout << bitree_io(root) << endl;
        rotate_print(root);
        cout << "===================================" << endl;
        bitree_destroy(root);
    }
    return 0;
}

} // namespace exb_7_3_40

