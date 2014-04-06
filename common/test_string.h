#ifndef TEST_STRING_H
#define TEST_STRING_H

#include <string>

#include "test.h"

class StringRunner : public _Runner<std::string>
{
public:

    virtual std::string * create_object()
    {
        std::string * s = new std::string;
        std::getline(std::cin, *s);
        if (!std::cin) {
            delete s;
            return NULL;
        }
        return s;
    }

    virtual void destroy(std::string * obj)
    {
        delete obj;
    }

    virtual void exec(std::string * obj) = 0;

};

#define CLASS_STRING_RUNNER \
class Runner : public StringRunner \
{ \
public: \
    virtual void exec(std::string * obj); \
};

#endif
