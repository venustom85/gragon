#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
#include <new>

#include "base.h"

template <typename T>
struct ListNode
{
    ListNode<T> * prev;
    T data;
    ListNode<T> * next;

    ListNode() : prev(NULL), data(), next(NULL) {}
    ListNode(T d) : prev(NULL), data(d), next(NULL) {}
};

template <typename T>
ListNode<T> * list_read(std::istream &in, int &length)
{
    in >> length;
    if (!in) {
        gragon::set_error_message("NO length of list found in stream");
        return NULL;
    }

    if (length <= 0) {
        sprintf(gragon::get_error_buf(), "ERROR length of list: %d", length);
        return NULL;
    }

    ListNode<T> * head = NULL;
    ListNode<T> * tail = NULL;
    T data;

    for (int i = 0; i < length; ++i) {
        in >> data;
        if (!in) {
            sprintf(gragon::get_error_buf(), "UNABLE to read list[%d]", i);
            list_destroy(head);
            return NULL;
        }

        try {
            ListNode<T> * node = new ListNode<T>(data);
            if (tail == NULL) {
                head = tail = node;
            } else {
                node->prev = tail;
                tail->next = node;
                tail = node;
            }
        } catch (std::bad_alloc & e) {
            sprintf(gragon::get_error_buf(), "FAILED to allocate list node [%d]", i);
            list_destroy(head);
            return NULL;
        }
    }

    return head;
}

template <typename T>
ListNode<T> * list_read(std::istream &in)
{
    int length = 0;
    return list_read<T>(in, length);
}

template <typename T>
ListNode<T> * list_read_from_file(const char *filename, int &length)
{
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "FAILED to open file: " << filename << '\n';
        return NULL;
    }

    return list_read<T>(fin, length);
}

template <typename T>
ListNode<T> list_read_from_file(const char *filename)
{
    int length = 0;
    return list_read_from_file<T>(filename, length);
}

template <typename T>
void list_destroy(ListNode<T> * head)
{
    ListNode<T> * p = NULL;
    while (head) {
        p = head;
        head = head->next;
        delete p;
    }
}

template <typename T>
ListNode<T> * list_add_head_node(ListNode<T> * head)
{
    ListNode<T> * new_head = new ListNode<T>;
    new_head->next = head;
    if (head != NULL) {
        head->prev = new_head;
    }
    return new_head;
}

template <typename T>
std::ostream & list_print(ListNode<T> * head)
{
    std::cout << '[';
    while (head != NULL) {
        std::cout << head->data << ' ';
        head = head->next;
    }
    return std::cout << ']';
}

template <typename T>
std::ostream & list_print(ListNode<T> * begin, ListNode<T> * end)
{
    std::cout << '[';
    while (begin != NULL && begin != end) {
        std::cout << begin->data << ' ';
        begin = begin->next;
    }
    return std::cout << ']';
}

#endif
