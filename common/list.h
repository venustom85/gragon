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
    
    ListNode(const ListNode<T> & n)
        : prev(NULL), data(n.data), next(NULL)
    {}

    ListNode<T> & operator= (const ListNode<T> & n)
    {
        if (this != &n) {
            data = n.data;
        }
        return (*this);
    }

};


template <typename T> ListNode<T> * list_read(std::istream &in, int &length);
template <typename T> ListNode<T> * list_read(std::istream &in);
template <typename T> ListNode<T> * list_read_from_file(const char *filename, int &length);
template <typename T> ListNode<T> list_read_from_file(const char *filename);
template <typename T> void list_destroy(ListNode<T> * head);
template <typename T> ListNode<T> * list_add_head_node(ListNode<T> * head);
template <typename T> std::ostream & list_print(ListNode<T> * head);
template <typename T> std::ostream & operator<< (std::ostream & out, ListNode<T> * head);
template <typename T> std::ostream & list_print(ListNode<T> * begin, ListNode<T> * end);
template <typename T> ListNode<T> * list_clone(ListNode<T> * head);

/**
 * Converte to a circular list with rear pointer
 * @param head - head pointer of original list.
 * @return rear pointer of the circular list
 */
template <typename T>
ListNode<T> * list_to_circular(ListNode<T> * head);

template <typename T> void list_destroy_circular(ListNode<T> * rear);
template <typename T> std::ostream & list_print_circular(ListNode<T> * rear);


template <typename T>
ListNode<T> * list_read(std::istream &in, int &length)
{
    in >> length;
    if (!in) {
        gragon::set_error_message("NO length of list found in stream");
        length = -1;
        return NULL;
    }

    if (length < 0) {
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
std::ostream & operator<< (std::ostream & out, ListNode<T> * head)
{
    return list_print<T>(head);
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

template <typename T>
ListNode<T> * list_clone(ListNode<T> * head)
{
    typedef ListNode<T> node_t;
    node_t c_head;
    node_t * c = &c_head;
    node_t * n = NULL;
    while (head != NULL) {
        n = new node_t(*head);
        n->prev = c;
        c->next = n;
        c = n;
        head = head->next;
    }

    if (c_head.next != NULL) {
        c_head.next->prev = NULL;
    }
    return c_head.next;
}

template <typename T>
ListNode<T> * list_to_circular(ListNode<T> * head)
{
    if (head == NULL) {
        return NULL;
    }

    ListNode<T> * r = head;
    while (r->next != NULL) {
        r = r->next;
    }

    r->next = head;
    head->prev = r;
    return r;
}

template <typename T>
void list_destroy_circular(ListNode<T> * rear)
{
    if (rear == NULL) {
        return;
    }

    ListNode<T> * head = rear->next;
    rear->next = NULL;
    list_destroy(head);
}

template <typename T>
std::ostream & list_print_circular(ListNode<T> * rear)
{
    if (rear == NULL) {
        return list_print(rear);
    }

    ListNode<T> * head = rear->next;
    rear->next = NULL;
    std::ostream & out = list_print(head);
    rear->next = head;
    return out;
}

#endif
