#include <cstring>

#include "base.h"

namespace {

    const int g_error_buf_size = 2048;

    char g_error_buf[g_error_buf_size] = {0};

}

namespace gragon {

const char * get_error_message()
{
    return g_error_buf;
}

void set_error_message(const char * msg)
{
    strncpy(g_error_buf, msg, g_error_buf_size - 1);
}

char * get_error_buf()
{
    return g_error_buf;
}

}
