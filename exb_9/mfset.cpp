/*
   等价类划分
  */
#include <iostream>
#include <cstring>
#include <map>
using namespace std;

namespace exb_9_mfset {

struct mf_node
{
    char ch;
    int parent;
};

struct eq_pair
{
    char a;
    char b;
};

int locate(mf_node * mfs, int i)
{
    int p = i;
    while (mfs[p].parent >= 0) {
        p = mfs[p].parent;
    }

    for (int k = i, t = -1; k != p; k = t) {
        t = mfs[k].parent;
        mfs[k].parent = p;
    }

    return p;
}

void merge(mf_node * mfs, int i, int j)
{
    if (mfs[i].parent < mfs[j].parent) {
        mfs[i].parent += mfs[j].parent;
        mfs[j].parent = i;
    } else {
        mfs[j].parent += mfs[i].parent;
        mfs[i].parent = j;
    }
}

void print_belong_to(const char * str, const eq_pair * pairs, int size)
{
    if (str == NULL || pairs == NULL || size < 0) {
        return;
    }

    int num_chars = (int) strlen(str);

    mf_node * mfs = new mf_node[num_chars];
    map<char,int> ch_index;
    for (int i = 0; i < num_chars; ++i) {
        mfs[i].ch = str[i];
        mfs[i].parent = -1;
        ch_index[str[i]] = i;
    }

    for (int i = 0; i < size; ++i) {
        int m = locate(mfs, ch_index[pairs[i].a]);
        int n = locate(mfs, ch_index[pairs[i].b]);
        merge(mfs, m, n);
    }

    for (int i = 0; i < num_chars; ++i) {
        int root = locate(mfs, i);
        cout << mfs[i].ch << " --> " << mfs[root].ch << endl;
    }

    delete[] mfs;
}

int g_main(int argc, char ** argv)
{
    int num_chars, num_pairs;
    cin >> num_chars >> num_pairs;
    
    char * char_buf = new char[num_chars + 1];
    char_buf[num_chars] = 0;
    for (int i = 0; i < num_chars; ++i) {
        cin >> char_buf[i];
    }

    eq_pair * pairs = new eq_pair[num_pairs];
    for (int i = 0; i < num_pairs; ++i) {
        cin >> pairs[i].a >> pairs[i].b;
    }

    print_belong_to(char_buf, pairs, num_pairs);

    delete[] pairs;
    delete[] char_buf;

    return 0;
}

} // namespace exb_9_mfset

