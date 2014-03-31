/*
   p28 2-2-16

   用顺序表表示集合，设计一个算法实现集合的求交集运算。

   */
#include "common/array.h"
#include "common/test_array.h"
using namespace std;

namespace {

    int intersection(int * a1, int s1, int * a2, int s2, int * r);

}

namespace ns_exb_2_2_16 {

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

        int len = min(a1.length, a2.length);
        int * buf = new int[len];

        len = intersection(a1.array, a1.length, a2.array, a2.length, buf);
        cout << "Intersection: " << ArrayObject<int>(buf, len) << '\n';

        delete[] buf;
    }
};

} // namespace ns_exb_2_2_16

int exb_2_2_16(int argc, char ** argv)
{
    ns_exb_2_2_16::Runner r("2_16.input");
    return r.run(argc, argv);
}

namespace {

int intersection(int * a1, int s1, int * a2, int s2, int * r)
{
    if (a1 == NULL || a2 == NULL || r == NULL || s1 < 0 || s2 < 0) {
        return -1;
    }

    int sr = 0;
    for (int i = 0; i < s1; ++i) {
        if (s2 == 0) {
            break;
        }

        for (int j = 0; j < s2; ++j) {
            if (a1[i] == a2[j]) {
                r[sr++] = a1[i];
                if (j < s2 - 1) {
                    int temp = a2[j];
                    a2[j] = a2[s2-1];
                    a2[s2-1] = temp;
                    --s2;
                }
            }
        }
    }

    return sr;
}

}
