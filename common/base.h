#ifndef BASE_H
#define BASE_H

#include <sstream>

namespace gragon {

    char * get_error_buf();

    const char * get_error_message();

    void set_error_message(const char * msg);

}

#endif
