/*
   构造哈夫曼编码
  */
#include <string>
#include <limits>
#include <iostream>
#include <cstring>
using namespace std;

namespace exb_7_hfm {

struct Elem
{
    const char * str;
    double weight;
};

struct Code
{
    const char * str;
    char * code;
    double weight;
};

struct HFNode
{
    double weight;
    int lc, rc, parent;
};

HFNode * create_hf(Elem * e, int size)
{
    if (e == NULL || size <= 0) {
        return NULL;
    }

    int n = size * 2 - 1;
    HFNode * hf = new HFNode[n];

    for (int i = 0; i < size; ++i) {
        hf[i].parent = -1;
        hf[i].weight = e[i].weight;
    }

    for (int i = size; i < n; ++i) {
        double m1, m2;
        m1 = m2 = numeric_limits<double>::max();
        int p1 = -1, p2 = -1;
        for (int k = 0; k < i; ++k) {
            if (hf[k].parent != -1) {
                continue;
            }
            double w = hf[k].weight;
            if (w < m1) {
                m2 = m1;
                p2 = p1;
                m1 = w;
                p1 = k;
            } else if (w < m2) {
                m2 = w;
                p2 = k;
            }
        }
        hf[i].lc = p1;
        hf[i].rc = p2;
        hf[i].weight = m1 + m2;
        hf[i].parent = -1;
        hf[p1].parent = hf[p2].parent = i;
    }

    return hf;
}

Code * huffman_code(Elem * e, int size)
{
    HFNode * hf = create_hf(e, size);
    if (hf == NULL) {
        return NULL;
    }

    Code * codes = new Code[size];
    char * buf = new char[size];
    int p = 0;

    for (int i = 0; i < size; ++i) {
        p = 0;
        int k = i;
        while (hf[k].parent != -1) {
            int pi = hf[k].parent;
            if (hf[pi].lc == k) {
                buf[p++] = '0';
            } else {
                buf[p++] = '1';
            }
            k = pi;
        }

        codes[i].str = e[i].str;
        codes[i].weight = e[i].weight;
        codes[i].code = new char[p+1];
        codes[i].code[p] = 0;
        for (int j = 0; j < p; ++j) {
            codes[i].code[j] = buf[p-1-j];
        }
    }

    delete[] hf;
    return codes;
}

struct hf_tree_node
{
    int index;
    double weight;
    hf_tree_node * lc;
    hf_tree_node * rc;
};

hf_tree_node * create_hf_tree(Elem * e, int size)
{
    if (e == NULL || size <= 0) {
        return NULL;
    }

    hf_tree_node ** nodes = new hf_tree_node* [size];
    for (int i = 0; i < size; ++i) {
        nodes[i] = new hf_tree_node;
        nodes[i]->index = i;
        nodes[i]->weight = e[i].weight;
        nodes[i]->lc = NULL;
        nodes[i]->rc = NULL;
    }

    int s = size;
    while (s > 1) {
        double m1, m2;
        m1 = m2 = numeric_limits<double>::max();
        int p1 = -1, p2 = -1;
        for (int i = 0; i < s; ++i) {
            double w = nodes[i]->weight;
            if (w < m1) {
                m2 = m1;
                p2 = p1;
                m1 = w;
                p1 = i;
            } else if (w < m2) {
                m2 = w;
                p2 = i;
            }
        }

        hf_tree_node * node = new hf_tree_node;
        node->lc = nodes[p1];
        node->rc = nodes[p2];
        node->weight = m1 + m2;

        nodes[p1] = node;
        nodes[p2] = nodes[s - 1];

        --s;
    }

    hf_tree_node * root = nodes[0];
    delete[] nodes;
    return root;
}

void gen_code(hf_tree_node * root, Code * codes, char * buf, int p)
{
    if (root == NULL) {
        return;
    }

    if (root->lc == NULL && root->rc == NULL) {
        buf[p] = 0;
        char * code = new char[p + 1];
        strcpy(code, buf);

        int i = root->index;
        codes[i].code = code;
        codes[i].weight = root->weight;
        return;
    }

    buf[p] = '0';
    gen_code(root->lc, codes, buf, p + 1);

    buf[p] = '1';
    gen_code(root->rc, codes, buf, p + 1);
}

Code * huffman_code_2(Elem * e, int size)
{
    hf_tree_node * hf_tree = create_hf_tree(e, size);
    if (hf_tree == NULL) {
        return NULL;
    }

    Code * codes = new Code[size];
    char * buf = new char[size];

    gen_code(hf_tree, codes, buf, 0);
    for (int i = 0; i < size; ++i) {
        codes[i].str = e[i].str;
    }

    return codes;
}

int g_main(int argc, char ** argv)
{
    int n;
    cin >> n;
    if (n <= 0) {
        return 1;
    }

    Elem * e = new Elem[n];
    string str;
    for (int i = 0; i < n; ++i) {
        cin >> str >> e[i].weight;
        char * s = new char[str.size() + 1];
        strcpy(s, str.c_str());
        e[i].str = s;
    }

    Code * codes = huffman_code_2(e, n);

    for (int i = 0; i < n; ++i) {
        cout << codes[i].str << ' ' << codes[i].weight << ' '
            << codes[i].code << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete[] e[i].str;
    }
    delete[] e;
    for (int i = 0; i < n; ++i) {
        delete[] codes[i].code;
    }
    delete[] codes;

    return 0;
}

} // namespace exb_7_hfm

