/*
   p140 5-2-6

   设计一个算法RepStr(s,i,j,t)，在串s中将第i个字符开始的j个字符构成的子串用串t替换，并返回产生的新串。
  */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

namespace exb_5_2_6 {

char * replace(const char * str, int i, int j, const char * t)
{
    if (str == NULL || t == NULL || i < 0 || j < 0) {
        return NULL;
    }

    int s_len = (int) strlen(str);

    if (i >= s_len) {
        char * new_str = new char[s_len + 1];
        strcpy(new_str, str);
        return new_str;
    }

    int t_len = (int) strlen(t);
    int new_len = 0;
    if (i + j > s_len) {
        new_len = i + t_len;
    } else {
        new_len = s_len + t_len - j;
    }

    char * new_str = new char[new_len + 1];
    new_str[new_len] = 0;

    strncpy(new_str, str, i);

    strcpy(new_str + i, t);

    if (i + j < s_len) {
        char * p = new_str + i + t_len;
        int k = i + j;
        while (k < s_len) {
            *p++ = str[k++];
        }
    }

    return new_str;
}

int g_main(int argc, char ** argv)
{
    string s, t;
    int i, j;

    while (cin >> s >> i >> j >> t) {
        char * new_str = replace(s.c_str(), i, j, t.c_str());
        cout << s << ' ' << i << ' ' << j << ' ' << t << endl;
        cout << "new string: ";
        if (new_str != NULL) {
            cout << new_str << endl;
        } else {
            cout << "NULL" << endl;
        }
        delete[] new_str;
    }

    return 0;
}

} // namespace exb_5_2_6

