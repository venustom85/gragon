/*
   p29 2-2-18

   用顺序表表示集合，设计一个算法实现集合的求差集运算。

   */
#include "common/array.h"
#include "common/test_array.h"
using namespace std;

namespace exb_2_2_18 {

int get_differ(int * a1, int s1, int * a2, int s2, int * r);

class Runner : public MultiArrayRunner<int>
{
public:
    Runner(const char * filename)
        : MultiArrayRunner<int>(filename, 2)
    {}

    void exec(Arrays * obj)
    {
        ArrayObject<int> a1 = obj->at(0);
        ArrayObject<int> a2 = obj->at(1);

        cout << "A1: " << a1 << '\n';
        cout << "A2: " << a2 << '\n';

        int len = a1.length;
        int * buf = new int[len];

        len = get_differ(a1.array, a1.length, a2.array, a2.length, buf);
        cout << "Differ: " << ArrayObject<int>(buf, len) << '\n';

        delete[] buf;
    }
};

int g_main(int argc, char ** argv)
{
    Runner r("2_18.input");
    return r.run(argc, argv);
}

int get_differ(int * a1, int s1, int * a2, int s2, int * r)
{
    if (a1 == NULL || a2 == NULL || r == NULL || s1 < 0 || s2 < 0) {
        return -1;
    }
    
    int sr = 0;

    for (int i = 0; i < s1; ++i) {
        int j = 0;
        bool exists = false;
        for (; j < s2; ++j) {
            if (a1[i] == a2[j]) {
                if (j < s2 - 1) {
                    int temp = a2[j];
                    a2[j] = a2[s2-1];
                    a2[s2-1] = temp;
                }
                --s2;
                exists = true;
                break;
            }
        }
        if (j == s2 && !exists) {
            r[sr++] = a1[i];
        }
    }

    return sr;
}

}

