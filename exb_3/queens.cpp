/*
   Find N queens result count
  */
#include <iostream>
#include <cstdlib>
using namespace std;

namespace exb_3_queens {

void n_queens_1_impl(int * loc, int k, int n, int & counter)
{
    if (k == n) {
        ++counter;
        return;
    }

    for (int i = 0; i < n; ++i) {
        int j = 0;
        for (; j < k; ++j) {
            if (i == loc[j]) {
                break;
            } else if (abs(k - j) == abs(i - loc[j])) {
                break;
            }
        }
        if (j == k) {
            loc[k] = i;
            n_queens_1_impl(loc, k + 1, n, counter);
        }
    }
}

int n_queens_1(int n)
{
    if (n <= 0) {
        return 0;
    }

    int * location = new int[n];

    int count = 0;

    n_queens_1_impl(location, 0, n, count);

    delete[] location;

    return count;
}

int n_queens_2(int n)
{
    if (n <= 0) {
        return 0;
    }

    int counter = 0;
    int * loc = new int[n];
    loc[0] = -1;
    int sp = 0;

    while (sp > -1) {
        if (sp == n) {
            ++counter;
            --sp;
            continue;
        }

        ++loc[sp];
        if (loc[sp] == n) {
            --sp;
            continue;
        }

        int i = 0;
        for (; i < sp; ++i) {
            if (loc[i] == loc[sp]) {
                break;
            } else if (abs(sp - i) == abs(loc[sp] - loc[i])) {
                break;
            }
        }

        if (i == sp) {
            ++sp;
            if (sp < n) {
                loc[sp] = -1;
            }
        }
    }

    delete[] loc;
    return counter;
}

int g_main(int argc, char ** argv)
{
    int n;
    while (cin >> n) {
        int c = n_queens_1(n);
        cout << "n = " << n << ", c1 = " << c << endl;
        
        c = n_queens_2(n);
        cout << "n = " << n << ", c2 = " << c << endl;
    }

    return 0;
}

} // namespace exb_3_queens

