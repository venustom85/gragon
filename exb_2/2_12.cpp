/*

  p26

  设计一个高效算法，从顺序表中删除所有元素值为x的元素，要求空间复杂度为O(1)。

 */
#include "common/array.h"
using namespace std;
using namespace gragon;

namespace {

    int remove_x(int * arr, int length, int x);

    int remove_x_2(int * arr, int length, int x);

}

int exb_2_2_12(int argc, char *argv[])
{
    const char * filename = "2_12.input";
    ifstream fin(filename);
    if (!fin) {
        cerr << "FAILED to open file " << filename << endl;
        return 1;
    }

    int length = 0;
    int * arr = NULL;
    int x = 0;
    int count = 0;

    while (true) {
        arr = array_read<int>(fin, length);
        if (arr == NULL) {
            break;
        }

        fin >> x;
        if (!fin) {
            cerr << "FAILED to read x" << endl;
            break;
        }

        ++count;

        cout << "Case " << count << "; ";
        array_print(arr, length) << '\n';
        cout << "To remove " << x << endl;
        //length = remove_x(arr, length, x);
        length = remove_x_2(arr, length, x);
        cout << "Result: ";
        array_print(arr, length) << "\n\n";

        array_destroy(arr);
    }

    return 0;
}

namespace {

int remove_x(int * arr, int length, int x)
{
    int x_c = 0;
    for (int i = 0; i < length; ++i) {
        if (arr[i] == x) {
            ++x_c;
        } else if (x_c > 0) {
            arr[i - x_c] = arr[i];
        }
    }
    return length - x_c;
}

int remove_x_2(int * arr, int length, int x)
{
    int i = 0, j = 0;
    for (i = 0; i < length && arr[i] != x; ++i)
        ;

    for (j = i + 1; j < length; ++j) {
        if (arr[j] != x) {
            arr[i] = arr[j];
            ++i;
        }
    }

    return i;
}

}
