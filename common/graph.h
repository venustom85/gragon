#ifndef GRAPH_H
#define GRAPH_H 1

#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>

enum GraphType
{
    UNDIGRAPH = 0x00,
    DIGRAPH = 0x01,
    UNDINET = 0X02,
    DINET = 0X03
};

inline bool is_directed(GraphType type) { return type & 0x01; }
inline bool is_weighted(GraphType type) { return type & 0x02; }

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

template <typename V, typename E = int>
struct AdjList
{
    struct ArcNode
    {
        int id;
        E   weight;
    };

    GraphType type;
    int num_vertex;
    int num_edges;
    V * vertex;

    ArcNode * arc_heads;
};

// ---------------------------------------------------------------------

template <typename V, typename E>
AdjMatrix<V,E> * adj_matrix_read(std::istream & in, GraphType type);

template <typename V>
AdjMatrix<V,int> * adj_matrix_read(std::istream & in, GraphType type)
{ return adj_matrix_read<V,int>(in, type); }

template <typename V, typename E>
AdjList<V,E> * adj_list_read(std::istream & in, GraphType type);

template <typename V>
AdjList<V,int> * adj_list_read(std::istream & in, GraphType type)
{ return adj_list_read<V,int>(in, type); }

template <typename G>
std::ostream & graph_print(std::ostream & out, const G * graph)
{ return out << graph; }

template <typename V, typename E>
std::ostream & operator<< (std::ostream & out, const AdjMatrix<V,E> * am);

template <typename V, typename E>
std::ostream & operator<< (std::ostream & out, const AdjList<V,E> * a);

template <typename V, typename E>
void graph_destroy(AdjMatrix<V,E> * am);

template <typename V, typename E>
void graph_destroy(AdjList<V,E> * a);

// ---------------------------------------------------------------------

template <typename V, typename E>
AdjMatrix<V,E> * adj_matrix_read(std::istream & in, GraphType type)
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

    std::map<V,int> v_map;
    for (int i = 0; i < num_vertex; ++i) {
        in >> am->vertex[i];
        v_map[am->vertex[i]] = i;
    }

    V v1, v2;
    E e;
    for (int i = 0; i < num_edges; ++i) {
        if (is_weighted(type)) {
            in >> v1 >> v2 >> e;
        } else {
            in >> v1 >> v2;
            e = E(1);
        }

        int row = v_map[v1];
        int col = v_map[v2];
        edges[row * num_vertex + col] = e;

        if (!is_directed(type)) {
            edges[col * num_vertex + row] = e;
        }
    }

    return am;
}

template <typename G>
const char * type_to_string(const G * graph)
{
    switch (graph->type) {
        case UNDIGRAPH: return "UNDIGRAPH";
        case DIGRAPH: return "DIGRAPH";
        case UNDINET: return "UNDINET";
        case DINET: return "DINET";
        default: return "UNKNOWN";
    }
}

template <typename T>
std::ostream & output(std::ostream & out, const T & t)
{
    return out << std::setw(10) << t;
}

inline std::ostream & output(std::ostream & out, double d)
{
    return out << std::setprecision(4) << std::setw(10) << d;
}

template <typename V, typename E>
std::ostream & operator<< (std::ostream & out, const AdjMatrix<V,E> * am)
{
    out << "type:   " << type_to_string(am) << '\n';
    out << "vertex: " << am->num_vertex << '\n';
    out << "edges:  " << am->num_edges << '\n';
    for (int i = 0; i < am->num_vertex; ++i) {
        out << '[' << i << ']' << am->vertex[i] << "  ";
    }
    out << '\n';

    for (int i = 0; i < am->num_vertex; ++i) {
        for (int j = 0; j < am->num_vertex; ++j) {
            output(out, am->edges[i * am->num_vertex + j]);
        }
        out << '\n';
    }

    return out;
}

template <typename V, typename E>
void graph_destroy(AdjMatrix<V,E> * am)
{
    delete[] vertex;
    delete[] edges;
    delete am;
}

#endif
