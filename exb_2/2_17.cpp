/*
   p29 2-2-17

   用顺序表表示集合，设计一个算法实现集合的求并集运算。

   */
#include "common/array.h"
#include "common/test_array.h"
using namespace std;

namespace {

    int get_union(int * a1, int s1, int * a2, int s2, int * r);

}

namespace ns_exb_2_2_17 {

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

        int len = a1.length + a2.length;
        int * buf = new int[len];

        len = get_union(a1.array, a1.length, a2.array, a2.length, buf);
        cout << "Union: " << ArrayObject<int>(buf, len) << '\n';

        delete[] buf;
    }
};

} // namespace ns_exb_2_2_17

int exb_2_2_17(int argc, char ** argv)
{
    ns_exb_2_2_17::Runner r("2_17.input");
    return r.run(argc, argv);
}

namespace {

int get_union(int * a1, int s1, int * a2, int s2, int * r)
{
    if (a1 == NULL || a2 == NULL || r == NULL || s1 < 0 || s2 < 0) {
        return -1;
    }

    int sr = 0;

    for (int i = 0; i < s1; ++i) {
        r[sr++] = a1[i];
    }

    int k = 0;
    for (; k < s2; ++k) {
        int j = 0;
        bool exist = false;
        for (; j < s1; ++j) {
            if (r[j] == a2[k]) {
                if (j < s1 - 1) {
                    int temp = r[j];
                    r[j] = r[s1-1];
                    r[s1-1] = temp;
                }
                --s1;
                exist = true;
                break;
            }
        }

        if (j == s1 && !exist) {
            r[sr++] = a2[k];
        }
    }

    while (k < s2) {
        r[sr++] = a2[k++];
    }

    return sr;
}

}
