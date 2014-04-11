/*
   p142 5-2-9

   设计递归算法将一个字符串置逆
  */
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

namespace exb_5_2_9 {

void reverse_impl(char * begin, char * end)
{
    if (begin == end || begin + 1 == end) {
        return;
    }

    reverse_impl(begin + 1, end);

    char temp = *begin;
    for (char * p = begin + 1; p != end; ++p) {
        *(p-1) = *p;
    }
    *(end - 1) = temp;
}

void reverse(char * str)
{
    size_t len = strlen(str);
    reverse_impl(str, str + len);
}

int g_main(int argc, char ** argv)
{
    char buf[1024];
    while (cin >> buf) {
        cout << "original: " << buf << endl;
        reverse(buf);
        cout << "reverse: " << buf << endl;
        cout << "=========================" << endl;
    }
}

} // namespace exb_5_2_9

