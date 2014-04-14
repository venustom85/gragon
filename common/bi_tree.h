#ifndef BI_TREE_H
#define BI_TREE_H

#include <iostream>
#include <cstdlib>
#include <queue>
#include <cstdio>
#include <string>

#include "base.h"

template <typename T>
struct BiNode
{
    T data;

    BiNode<T> * lc;
    BiNode<T> * rc;

    BiNode(const T & t)
        : data(t), lc(NULL), rc(NULL)
    {}

    BiNode()
        : data(), lc(NULL), rc(NULL)
    {}
};

template <typename T>
struct bitree_io_wrapper
{
    bitree_io_wrapper(const BiNode<T> * root)
        : root(root)
    {}

    const BiNode<T> * root;
};

template <typename T>
bitree_io_wrapper<T> bitree_io(const BiNode<T> * root)
{
    return bitree_io_wrapper<T>(root);
}

// -----------------------------------------------

template <typename T>
BiNode<T> * bitree_read(std::istream & in);

template <typename T>
void bitree_destroy(BiNode<T> * & root);

template <typename T>
std::ostream & bitree_print(std::ostream & out, const BiNode<T> * & root);

template <typename T>
std::ostream & operator<< (std::ostream & out, const bitree_io_wrapper<T> & io);

// -----------------------------------------------

template <typename T>
BiNode<T> * bitree_read(std::istream & in)
{
    typedef BiNode<T> node_t;

    int node_count = 0;
    if (!(in >> node_count)) {
        gragon::set_error_message("FAILED to read node count of bi tree");
        return NULL;
    }

    if (node_count < 0) {
        char buf[256];
        sprintf(buf, "ERROR node count of bi tree: %d", node_count);
        gragon::set_error_message(buf);
        return NULL;
    }

    if (node_count == 0) {
        return NULL;
    }

    node_t * root = new node_t;
    in >> root->data;

    std::queue<node_t*> qu;
    qu.push(root);

    int counter = 1;

    while (!qu.empty() && counter < node_count) {
        T data, parent;
        char role;
        in >> data >> parent >> role;

        while (!qu.empty() && qu.front()->data != parent) {
            qu.pop();
        }

        if (qu.empty()) {
            continue;
        }

        node_t * parent_node = qu.front();
        node_t * node = new node_t(data);

        if (role == 'L') {
            parent_node->lc = node;
        } else {
            parent_node->rc = node;
            qu.pop();
        }

        qu.push(node);
        ++counter;
    }

    return root;
}

template <typename T>
void bitree_destroy(BiNode<T> * & root)
{
    if (root != NULL) {
        bitree_destroy(root->lc);
        bitree_destroy(root->rc);
        delete root;
        root = NULL;
    }
}

template <typename T>
std::ostream & bitree_print(std::ostream & out, const BiNode<T> * root)
{
    if (root == NULL) {
        return out;
    }

    out << root->data;

    bool has_child = root->lc != NULL || root->rc != NULL;
    if (has_child) {
        out << '(';
        bitree_print(out, root->lc);
        out << ',';
        bitree_print(out, root->rc);
        out << ')';
    }

    return out;
}

template <typename T>
std::ostream & operator<< (std::ostream & out, const bitree_io_wrapper<T> & io)
{
    return bitree_print(out, io.root);
}

#endif
