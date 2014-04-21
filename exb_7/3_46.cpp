/*
   p231 7-3-46

   将满二叉树的先序遍历序列转换为后序遍历序列。
  */
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

namespace exb_7_3_46 {

void to_post_order(const char * begin, const char * end)
{
    if (begin == NULL || end == NULL) {
        return;
    } else if (begin == end) {
        return;
    }

    if (begin + 1 == end) {
        cout << *begin;
        return;
    }

    int sub_length = (end - begin - 1) / 2;

    const char * left_begin = begin + 1;
    const char * right_begin = left_begin + sub_length;

    to_post_order(left_begin, left_begin + sub_length);
    to_post_order(right_begin, end);

    cout << *begin;
}

int g_main(int argc, char ** argv)
{
    string pre_seq;
    while (cin >> pre_seq) {
        cout << "pre order: " << pre_seq << endl;
        to_post_order(pre_seq.c_str(), pre_seq.c_str() + pre_seq.size());
        cout << endl;
        cout << "=================================" << endl;
    }
    return 0;
}

} // namespace exb_7_3_46

