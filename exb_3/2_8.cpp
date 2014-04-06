/*
   p82 3-2-8

   设以整数序列1,2,3,4作为顺序栈st的输入，利用push和pop操作，写出所有可能的输出并编程实现算法。
  */
#include <stack>
#include "common/test_array.h"
using namespace std;

namespace exb_3_2_8 {

typedef ArrayObject<int> array_t;

void find_all(int * begin, int * end, int * stk, int top, int * out, int p)
{
    if (top > 0) {
        int v = stk[top-1];
        out[p] = v;
        find_all(begin, end, stk, top - 1, out, p + 1);
        stk[top-1] = v;
    }

    if (begin != end) {
        stk[top] = *begin;
        find_all(begin + 1, end, stk, top + 1, out, p);
    }

    if (begin == end && top == 0) {
        array_println(out, p);
    }
}

void print_all_seq_by_push_pop(int * arr, int size)
{
    if (arr == NULL) {
        return;
    }

    int * stk = new int[size];
    int * out = new int[size];
    find_all(arr, arr + size, stk, 0, out, 0);
    delete[] stk;
    delete[] out;
}

CLASS_ARRAY_RUNNER(int,1);

void Runner::exec(Arrays * obj)
{
    array_t a = obj->at(0);
    cout << "Original list: " << a << endl;
    cout << "All possible sequence: " << endl;
    print_all_seq_by_push_pop(a.array, a.length);
}

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_3_2_8

