#ifndef TEST_H
#define TEST_H

#include <fstream>
#include <iostream>

template <typename T>
class _Runner
{
public:

    virtual ~_Runner() {}
    
    virtual bool init() = 0;

    virtual T * create_object() = 0;

    virtual void exec(T * obj) = 0;

    virtual void destroy(T * obj) = 0;

    virtual int run(int argc, char ** argv);

};

template <typename T>
class FileRunner : public _Runner<T>
{
public:

    FileRunner(const char *filename) 
        : _Runner<T>(), _filename(filename), _fin(filename) {}

    ~FileRunner();

    virtual bool init();

protected:

    const char * _filename;

    std::ifstream _fin;

};

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

    return 0;
}

template <typename T>
bool FileRunner<T>::init()
{
    if (!_fin) {
        std::cerr << "FAILED to open file " << _filename << '\n';
        return false;
    }
    return true;
}

template <typename T>
FileRunner<T>::~FileRunner()
{
    if (_fin) {
        _fin.close();
    }
}

#endif
