#ifndef GRAPH_H
#define GRAPH_H 1

#include <iostream>
#include <cstring>
#include <string>
#include <map>

enum GraphType
{
    UNDIGRAPH = 0x00,
    DIGRAPH = 0x01,
    UNDINET = 0X02,
    DINET = 0X03
};

bool is_directed(GraphType type) { return type & 0x01; }
bool is_weighted(GraphType type) { return type & 0x02; }

template <typename V, typename E = int>
struct AdjMatrix
{
    GraphType type;
    int num_vertex;
    int num_edges;
    V * vertex;
    E * edges;

    AdjMatrix() : vertex(NULL), edges(NULL) {}
    ~AdjMatrix() { delete[] vertex; delete[] edges; }
};

template <typename V, typename E>
AdjMatrix<V,E> adj_matrix_read(std::istream & in, GraphType type)
{
    int num_vertex, num_edges;
    if (!(in >> num_vertex >> num_edges)) {
        return NULL;
    } else if (num_vertex <= 0 || num_edges < 0) {
        return NULL;
    }

    AdjMatrix<V,E> * am = new AdjMatrix<V,E>;
    am->num_vertex = num_vertex;
    am->num_edges = num_edges;
    am->vertex = new V[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        am->vertex[i] = V();
    }

    int total = num_edges * num_edges;
    E * edges = new E[total];
    for (int i = 0; i < total; ++i) {
        edges[i] = E();
    }
    am->edges = edges;

    std::string line;
    geline(in, line);
    istringstream s_in(line);

    std::map<V,int> v_map;
    for (int i = 0; i < num_vertex; ++i) {
        s_in >> am->vertext[i];
        v_map[am->vertex[i]] = i;
    }

    V v1, v2;
    E e;
    for (int i = 0; i < num_edges; ++i) {
        getline(in, line);
        s_in.str(line);
        if (is_weighted(type)) {
            s_in >> v1 >> v2 >> e;
        } else {
            s_in >> v1 >> v2;
            e = E(1);
        }

        int row = v_map[v1];
        int col = v_map[v2];
        edges[row * num_edges + col] = e;

        if (!is_directed(type)) {
            edges[col * num_edges + row] = e;
        }
    }

    return am;
}

#endif
