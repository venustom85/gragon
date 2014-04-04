#ifndef TEST_H
#define TEST_H

#include <fstream>
#include <iostream>

template <typename T>
class _Runner
{
public:

    virtual ~_Runner() {}
    
    virtual bool init();

    virtual T * create_object() = 0;

    virtual void exec(T * obj) = 0;

    virtual void destroy(T * obj) = 0;

    virtual int run(int argc, char ** argv);

};

template <typename T>
bool _Runner<T>::init()
{
    return true;
}

template <typename T>
int _Runner<T>::run(int argc, char ** argv)
{
    if (!init()) {
        return 1;
    }

    int case_count = 0;
    while (true) {
        T * obj = create_object();
        if (obj == NULL) {
            break;
        }

        ++case_count;

        std::cout << "================================\n\n";
        std::cout << "CASE [" << case_count << "] \n";
        
        exec(obj);

        std::cout << "\n";

        destroy(obj);
    }

    std::cout << "================================\n";

    if (case_count == 0) {
        std::cout << "WARN: NO test case to run! Maybe the input file is empty?\n";
    }

    return 0;
}

#endif
