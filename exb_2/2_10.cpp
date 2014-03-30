/*
   
   已知一个顺序表L，其中的元素递增有序排列，设计一个算法插入一个元素x后保持该顺序表仍递增有序排列。
   
 */
#include "common/array.h"
using namespace std;
using namespace gragon;

namespace {

    bool insert(int * arr, int length, int element);

}

int exb_2_2_10(int argc, char ** argv)
{
    const char * filename = "2_10.input";
    ifstream fin(filename);
    if (!fin) {
        cerr << "FAILED to open file " << filename << endl;
        return 1;
    }

    int i = 0;
    while (true) {
        ++i;
        int length = 0;
        int * array = array_read<int>(fin, length);
        if (array != NULL) {
            array = array_expand(array, length);
        } else {
            break;
        }

        cout << "case " << i << ": ";
        array_print(array, length) << '\n';
        
        int num = 0;
        fin >> num;
        if (!fin) {
            cerr << "NEED num to insert\n";
            array_destroy(array);
            return 1;
        }

        cout << "insert: " << num << '\n';

        if (insert(array, length, num)) {
            length += 1;
        }

        cout << "result: ";
        array_print(array, length) << "\n\n";
        
        array_destroy(array);
    }

    fin.close();

    return 0;
}

namespace {

bool insert(int * arr, int length, int element)
{
    if (arr == NULL || length < 0) {
        return false;
    }

    int p = 0;
    while (p < length && arr[p] < element) {
        ++p;
    }

    for (int i = length - 1; i >= p; --i) {
        arr[i+1] = arr[i];
    }

    arr[p] = element;

    return true;
}

}
