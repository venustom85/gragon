/*

   p27 2-2-14

   设有一个顺序表L，其元素为整型数据，设计一个算法将L中所有小于0的整数放在前半部分，大于等于0的整数放在后半部分。

   */
#include "common/array.h"
using namespace std;

namespace {

    template <typename T, typename Cond>
    void partition(T * begin, T * end, Cond cond);

    struct compare_to_zero {
        bool operator() (int i) {
            return i < 0;
        }
    };

}

int exb_2_2_14(int argc, char ** argv)
{
    const char * filename = "2_14.input";
    ifstream fin(filename);
    if (!fin) {
        cerr << "FAILED to open file " << filename << endl;
        return 1;
    }

    int * array = NULL;
    int length = 0;
    int case_count = 0;

    while (true) {
        case_count++;
        array = array_read<int>(fin, length);
        if (array == NULL) {
            break;
        }

        cout << "Case " << case_count << ": ";
        array_print(array, length) << '\n';

        partition(array, array + length, compare_to_zero());

        cout << "Result: ";
        array_print(array, length) << "\n\n";

        array_destroy(array);
    }

    return 0;
}

namespace {

template <typename T, typename Cond>
void partition(T * begin, T * end, Cond cond)
{
    if (begin == NULL || end == NULL) {
        return;
    }

    --end;
    while (begin < end) {
        while (begin < end && cond(*begin)) {
            ++begin;
        }
        while (begin < end && !cond(*end)) {
            --end;
        }
        if (begin != end) {
            T temp = *begin;
            *begin = *end;
            *end = temp;
        }
    }
}

}
