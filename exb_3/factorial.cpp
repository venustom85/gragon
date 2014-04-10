/*
   Factorial calculate
  */
#include <stack>
#include <iostream>
using namespace std;

namespace exb_3_factorial {

long long factorial(int n)
{
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }

    return factorial(n - 1) * (long long) n;
}

struct frame
{
    int n;
    int step;
    long long v1;
    long long * rp;
};

long long factorial_2(int n)
{
    frame F;
    stack<frame> stk;

    long long result = 0;

    F.n = n;
    F.step = 0;
    F.rp = &result;
    stk.push(F);

    while (!stk.empty()) {
        frame & t = stk.top();
        if (t.step == 0) {
            if (t.n < 0) {
                *t.rp = 0;
                stk.pop();
            } else if (t.n == 0) {
                *t.rp = 1;
                stk.pop();
            } else {
                F.n = t.n - 1;
                F.step = 0;
                F.rp = &t.v1;
                t.step = 1;
                stk.push(F);
            }
        } else {
            *t.rp = t.v1 * (long long) t.n;
            stk.pop();
        }
    }

    return result;
}

int g_main(int argc, char ** argv)
{
    int n = 0;
    while (cin >> n) {
        long long r1 = factorial(n);
        long long r2 = factorial_2(n);
        cout << "n: " << n << ", fac_1 = " << r1 << ", fac_2 = " << r2 << endl;
    }
    return 0;
}

} // namespace exb_3_factorial

