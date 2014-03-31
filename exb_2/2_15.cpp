/*
   p28 2-2-15

   设计一个算法从顺序表中删除重复的元素，并使剩余元素间的相对次序保持不变。

   */
#include "common/test_array.h"
using namespace std;

namespace {

    int remove_duplicate(int * array, int length);

}

namespace ns_exb_2_2_15 {
class Runner : public SingleArrayRunner<int>
{
public:
    Runner(const char * filename) : SingleArrayRunner<int>(filename) {}

    void exec(ArrayObject<int> * obj)
    {
        cout << "Origin: ";
        array_print(obj->array, obj->length) << '\n';

        obj->length = remove_duplicate(obj->array, obj->length);

        cout << "Result: ";
        array_print(obj->array, obj->length) << '\n';
    }
};
}

int exb_2_2_15(int argc, char ** argv)
{
    ns_exb_2_2_15::Runner runner("2_15.input");
    return runner.run(argc, argv);
}

namespace {

int remove_duplicate(int * array, int length)
{
    int i = -1, j = 0;
    int k = 0;
    for (; j < length; ++j) {
        for (k = 0; k <= i; ++k) {
            if (array[k] == array[j]) {
                break;
            }
        }
        if (k > i) {
            ++i;
            array[i] = array[j];
        }
    }
    return i + 1;
}

}
