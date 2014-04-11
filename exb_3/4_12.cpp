/*
   p107 3-4-12

   设计求解ackerman函数的递归和非递归算法
  */
#include <iostream>
#include <stack>
using namespace std;

namespace exb_3_4_12 {

long long ackerman(int m, int n)
{
    if (m == 0) {
        return n + 1;
    }
    if (n == 0) {
        return ackerman(m - 1, 1);
    }
    return ackerman(m - 1, ackerman(m, n - 1));
}

struct frame
{
    int m, n;
    long long * rp;
    int step;
    long long r0, r1;
};

long long ackerman_2(int m, int n)
{
    frame F;
    stack<frame> stk;

    long long result = 0;
    F.m = m;
    F.n = n;
    F.step = 0;
    F.rp = &result;
    stk.push(F);

    while (!stk.empty()) {
        frame & t = stk.top();
        if (t.step == 0) {
            if (t.m == 0) {
                *t.rp = t.n + 1;
                stk.pop();
            } else if (t.n == 0) {
                F.m = t.m - 1;
                F.n = 1;
                F.step = 0;
                F.rp = &t.r0;
                t.step = 1;
                stk.push(F);
            } else {
                F.m = t.m;
                F.n = t.n - 1;
                F.step = 0;
                F.rp = &t.r1;
                t.step = 2;
                stk.push(F);
            }
        } else if (t.step == 1) {
            *t.rp = t.r0;
            stk.pop();
        } else if (t.step == 2) {
            F.m = t.m - 1;
            F.n = t.r1;
            F.step = 0;
            F.rp = &t.r0;
            t.step = 3;
            stk.push(F);
        } else {
            *t.rp = t.r0;
            stk.pop();
        }
    }

    return result;
}

int g_main(int argc, char ** argv)
{
    int m, n;

    while (cin >> m >> n) {
        long long r = ackerman(m, n);
        cout << "m = " << m << ", n = " << n << ", ackerman = " << r << endl;

        r = ackerman_2(m, n);
        cout << "m = " << m << ", n = " << n << ", ackerman_2 = " << r << endl;

        cout << "================================" << endl;
    }
}

} // namespace exb_3_4_12

