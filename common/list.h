#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
#include <new>

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
        std::cerr << "NO length of list found in stream\n";
        return NULL;
    }

    if (length <= 0) {
        std::cerr << "ERROR length of list: " << length << '\n';
        return NULL;
    }

    ListNode<T> * head = NULL;
    ListNode<T> * tail = NULL;
    T data;

    for (int i = 0; i < length; ++i) {
        in >> data;
        if (!in) {
            std::cerr << "UNABLE to read list[" << i << "]\n";
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
            std::cerr << "FAILED to allocate list node [" << i << "]\n";
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
    return list_read(in, length);
}

template <typename T>
ListNode<T> * list_read_from_file(const char *filename, int &length)
{
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "FAILED to open file: " << filename << '\n';
        return NULL;
    }

    return list_read(fin, length);
}

template <typename T>
ListNode<T> list_read_from_file(const char *filename)
{
    int length = 0;
    return list_read_from_file(filename, length);
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

#endif
