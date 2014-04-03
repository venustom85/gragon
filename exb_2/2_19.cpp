/*
   p29 2-2-19

   用顺序表A和B表示的两个线性表，元素的个数分别为m和n，若表中数据都是从小到大顺序排列的，且这(m+n)个数据中没有重复的。
   (1) 设计一个算法将此两个线性表合并成一个，仍是数据由小到大排列的线性表，存储到另一个顺序表C中。
   (2) 如果顺序表B的大小为(m+n)个单元，是否可不利用顺序表C而将合并成的线性表存放于顺序表B中？试设计此算法。
   (3) 设顺序表A有m+n个元素，且前m个有序，后n个有序，设计一个算法，使得整个顺序表有序。

   */
#include "common/test_array.h"
using namespace std;

namespace exb_2_2_19 {


int merge_out(int * a, int m, int * b, int n, int * c)
{
    if (a == NULL || b == NULL || c == NULL) {
        return -1;
    }

    int ci = 0;
    int ai = 0, bi = 0;
    for (; ai < m && bi < n; ) {
        if (a[ai] < b[bi]) {
            c[ci++] = a[ai++];
        } else {
            c[ci++] = b[bi++];
        }
    }

    while (ai < m) {
        c[ci++] = a[ai++];
    }

    while (bi < n) {
        c[ci++] = b[bi++];
    }

    return ci;
}

int merge_in(int * a, int m, int * b, int n)
{
    if (a == NULL || b == NULL) {
        return -1;
    }

    for (int i = m + n - 1; i >= m; --i) {
        b[i] = b[i-m];
    }

    int ai = 0, bi = m, ci = 0;
    for (; ai < m && bi < m + n; ) {
        if (a[ai] < b[bi]) {
            b[ci++] = a[ai++];
        } else {
            b[ci++] = b[bi++];
        }
    }

    while (ai < m) {
        b[ci++] = a[ai++];
    }

    return m + n;
}

int merge_part(int * a, int m, int n)
{
    if (a == NULL) {
        return -1;
    }

    int ai = 0, bi = m, p = 0, t = 0;
    for (; bi < m + n; ++bi) {
        for (p = ai; p < bi && a[p] < a[bi]; ++p)
            ;
        ai = p;
        t = a[bi];
        for (p = bi - 1; p >= ai; --p) {
            a[p+1] = a[p];
        }
        a[ai] = t;
    }

    return m + n;
}

class Runner : public MultiArrayRunner<int>
{
public:
    Runner()
        : MultiArrayRunner<int>(2)
    {}

    void exec(Arrays * obj)
    {
        ArrayObject<int> a1 = obj->at(0);
        ArrayObject<int> a2 = obj->at(1);

        cout << "A1: " << a1 << '\n';
        cout << "A2: " << a2 << '\n';

        // merge a and b into c;
        int length_c = a1.length + a2.length;
        int * c = new int[length_c];
        length_c = merge_out(a1.array, a1.length, a2.array, a2.length, c);
        cout << "merge into c: " << ArrayObject<int>(c,length_c) << '\n';

        // merge into b;
        int length_b = a1.length + a2.length;
        int * b = c;
        for (int i = 0; i < a2.length; ++i) {
            b[i] = a2.array[i];
        }
        length_b = merge_in(a1.array, a1.length, b, a2.length);
        cout << "merge into A2: " << ArrayObject<int>(b,length_b) << '\n';

        int length_a = a1.length + a2.length;
        int * a = b; 
        for (int i = 0; i < a1.length; ++i) {
            a[i] = a1.array[i];
        }
        for (int i = 0; i < a2.length; ++i) {
            a[i+a1.length] = a2.array[i];
        }
        cout << "before merge a: " << ArrayObject<int>(a,length_a) << endl;
        length_a = merge_part(a, a1.length, a2.length);
        cout << "after merge in a: " << ArrayObject<int>(a,length_a) << endl;
        delete[] a;
    }
};

int g_main(int argc, char ** argv)
{
    Runner r;
    return r.run(argc, argv);
}

} // namespace exb_2_2_19
