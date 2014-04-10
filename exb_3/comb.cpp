/*
   print combination recursively and non-recursively
  */
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <stack>
using namespace std;

namespace exb_3_comb {

struct frame
{
    const char * str;
    int n;
    int m;
    int p;
    int step;
};

void print_combination_2(const char * str, int m)
{
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (m > (int)len) {
        return;
    } else if (m <= 0) {
        return;
    }

    char * buf = new char[len + 1];

    frame F;
    stack<frame> stk;

    F.str = str;
    F.n = (int) len;
    F.m = m;
    F.p = 0;

    stk.push(F);

    while (!stk.empty()) {
        frame & t = stk.top();
        if (t.step == 0) {
            if (t.m > t.n) {
                stk.pop();
            } else if (t.m == 0) {
                buf[t.p] = 0;
                cout << buf << endl;
                stk.pop();
            } else {
                t.step = 1;
                F.str = t.str + 1;
                F.n = t.n - 1;
                F.m = t.m;
                F.p = t.p;
                stk.push(F);
            }
        } else if (t.step == 1) {
            buf[t.p] = *t.str;
            t.step = 2;
            F.str = t.str + 1;
            F.n = t.n - 1;
            F.m = t.m - 1;
            F.p = t.p + 1;
            stk.push(F);
        } else {
            stk.pop();
        }
    }

    delete[] buf;
}

void print_comb(const char * str, int n, int m, char * buf, int p)
{
    if (m > n) {
        return;
    }

    if (m == 0) {
        buf[p] = 0;
        cout << buf << endl;
        return;
    }

    print_comb(str + 1, n - 1, m, buf, p);

    buf[p] = *str;

    print_comb(str + 1, n - 1, m - 1, buf, p + 1);
}

void print_combination_1(const char * str, int m)
{
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (m < 0) {
        return;
    } else if (m > (int)len) {
        return;
    }

    char * buf = new char[len + 1];

    print_comb(str, (int)len, m, buf, 0);

    delete[] buf;
}

int g_main(int argc, char ** argv)
{
    if (argc < 3) {
        cerr << "param: <string> <n>" << endl;
        exit(-1);
    }

    const char * str = argv[1];
    int n = atoi(argv[2]);
    print_combination_1(str, n);

    cout << "=========================" << endl;

    print_combination_2(str, n);
}

} // namespace exb_3_comb

