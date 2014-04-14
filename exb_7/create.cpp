/*
   以先中序和中后序建立二叉树
  */
#include <cstring>
#include <string>
#include "common/bi_tree.h"
using namespace std;

namespace exb_7_create {

typedef BiNode<char> node_t;

node_t * pre_and_in(const char * pre1, const char * pre2, const char * in1, const char * in2)
{
    if (pre1 == pre2 || in1 == in2) {
        return NULL;
    }

    const char * p_in = in1;
    while (p_in != in2 && *p_in != *pre1) {
        ++p_in;
    }

    if (p_in == in2) {
        return NULL;
    }

    node_t * node = new node_t(*pre1);

    int left_size = p_in - in1;

    node->lc = pre_and_in(pre1 + 1, pre1 + 1 + left_size, in1, p_in);

    node->rc = pre_and_in(pre1 + 1 + left_size, pre2, p_in + 1, in2);

    return node;
}

node_t * create_by_pre_and_in(const char * pre, const char * in)
{
    if (pre == NULL || in == NULL) {
        return NULL;
    }

    size_t pre_len = strlen(pre);
    size_t in_len = strlen(in);

    if (pre_len != in_len || pre_len == 0 || in_len == 0) {
        return NULL;
    }

    return pre_and_in(pre, pre + pre_len, in, in + in_len);
}

node_t * in_and_post(const char * in1, const char * in2, const char * post1, const char * post2)
{
    if (in1 == in2 || post1 == post2) {
        return NULL;
    }

    char root_data = *(post2 - 1);
    const char * p_in = in1;
    while (p_in != in2 && *p_in != root_data) {
        ++p_in;
    }

    if (p_in == in2) {
        return NULL;
    }

    int right_size = in2 - p_in - 1;

    node_t * node = new node_t(root_data);

    node->rc = in_and_post(p_in + 1, in2, post2 - right_size - 1, post2 - 1);

    node->lc = in_and_post(in1, p_in, post1, post2 - right_size - 1);

    return node;
}

node_t * create_by_in_and_post(const char * in, const char * post)
{
    if (in == NULL || post == NULL) {
        return NULL;
    }

    size_t in_len = strlen(in);
    size_t post_len = strlen(post);

    if (in_len != post_len) {
        return NULL;
    }

    return in_and_post(in, in + in_len, post, post + post_len);
}

int g_main(int argc, char ** argv)
{
    string pre, in, post;
    while (cin >> pre >> in >> post) {
        cout << "[pre] " << pre << endl;
        cout << "[in] " << in << endl;
        cout << "[post] " << post << endl;
        
        node_t * n1 = create_by_pre_and_in(pre.c_str(), in.c_str());
        node_t * n2 = create_by_in_and_post(in.c_str(), post.c_str());

        cout << "[n1] " << bitree_io(n1) << endl;
        cout << "[n2] " << bitree_io(n2) << endl;

        bitree_destroy(n1);
        bitree_destroy(n2);

        cout << "================================" << endl;
    }

    return 0;
}

} // namespace exb_7_create

