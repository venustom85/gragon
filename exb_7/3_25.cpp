/*
   p215 7-3-25

   假设二叉树采用链式存储结构，设计一个算法，求二叉树b的宽度（即具有结点数最多的那一层上的结点个数）。
  */
#include "common/bi_tree.h"
#include <vector>
#include <queue>
using namespace std;

namespace exb_7_3_25 {

typedef BiNode<char> node_t;

void get_width(const node_t * root, int level, vector<int> & counter)
{
    if (root == NULL) {
        return;
    }

    int size = (int) counter.size();
    if (level + 1 > size) {
        counter.push_back(0);
    }

    ++counter[level];

    get_width(root->lc, level + 1, counter);

    get_width(root->rc, level + 1, counter);
}

int get_width(const node_t * root)
{
    vector<int> nodes_per_level;
    get_width(root, 0, nodes_per_level);

    if (nodes_per_level.size() == 0) {
        return 0;
    }

    int level = 0, max = nodes_per_level[0];
    for (int i = 1; i < nodes_per_level.size(); ++i) {
        if (nodes_per_level[i] > max) {
            level = i;
            max = nodes_per_level[i];
        }
    }

    return max;
}

struct level_info
{
    const node_t * node;
    int level_num;
};

int get_width_2(const node_t * root)
{
    if (root == NULL) {
        return 0;
    }

    level_info info;
    info.node = root;
    info.level_num = 0;

    queue<level_info> qu;
    qu.push(info);

    queue<level_info> backup;

    while (!qu.empty()) {
        level_info & front = qu.front();
        backup.push(front);
        qu.pop();

        if (front.node->lc != NULL) {
            info.node = front.node->lc;
            info.level_num = front.level_num + 1;
            qu.push(info);
        }

        if (front.node->rc != NULL) {
            info.node = front.node->rc;
            info.level_num = front.level_num + 1;
            qu.push(info);
        }
    }

    int max = 0;
    int cur_level = 0;
    int c = 0;
    while (!backup.empty()) {
        level_info & info = backup.front();
        if (info.level_num == cur_level) {
            ++c;
        } else {
            if (max < c) {
                max = c;
            }
            c = 1;
            cur_level = info.level_num;
        }
        backup.pop();
    }

    if (c > max) {
        max = c;
    }

    return max;
}

int g_main(int argc, char ** argv)
{
    node_t * root = NULL;
    while ((root = bitree_read<char>(cin)) != NULL) {
        cout << "tree: " << bitree_io(root) << endl;
        cout << "width: " << get_width(root) << endl;
        cout << "width: " << get_width_2(root) << endl;
        cout << "======================================" << endl;
        bitree_destroy(root);
    }

    return 0;
}

} // namespace exb_7_3_25

