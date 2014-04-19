/*
   p226 7-3-39

   一棵二叉链树，利用结点的右子指针将叶子结点按从左往右的顺序串成一个单链表。
  */
#include "common/bi_tree.h"
using namespace std;

namespace exb_7_3_39 {

typedef BiNode<char> node_t;

void leaf_list(node_t * root, node_t * & tail)
{
    if (root == NULL) {
        return;
    }

    if (root->lc == NULL && root->rc == NULL) {
        tail->rc = root;
        tail = root;
        return;
    }

    leaf_list(root->lc, tail);
    leaf_list(root->rc, tail);
}

node_t * to_leaf_list(node_t * root)
{
    if (root == NULL) {
        return NULL;
    }

    node_t head_node;
    node_t * p_head = &head_node;

    leaf_list(root, p_head);

    return head_node.rc;
}

int g_main(int argc, char ** argv)
{
    node_t * root = NULL;
    int counter = 0;

    while ((root = bitree_read<char>(cin)) != NULL) {
        ++counter;
        cout << "CASE [" << counter << "] " << bitree_io(root) << endl;
        node_t * head = to_leaf_list(root);

        while (head != NULL) {
            cout << head->data << ' ';
            head = head->rc;
        }
        cout << endl;
        cout << "=================================" << endl;
    }
}

} // namespace exb_7_3_39

