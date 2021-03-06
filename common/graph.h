#ifndef GRAPH_H
#define GRAPH_H 1

#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <limits>

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
struct BaseGraph
{
    GraphType type;
    int num_vertex;
    int num_edges;

    V * vertex;

    BaseGraph() : num_vertex(0), num_edges(0), vertex(NULL) {}
    ~BaseGraph() { delete[] vertex; }

    typedef V vertex_t;
    typedef E weight_t;
};

template <typename V, typename E = int>
struct AdjMatrix : public BaseGraph<V,E>
{
    E * edges;

    AdjMatrix() : BaseGraph<V,E>(), edges(NULL) {}
    ~AdjMatrix() { delete[] edges; }

    E & e(int i, int j)
    {
        return edges[i * this->num_vertex + j];
    }

    const E & e(int i, int j) const
    {
        return edges[i * this->num_vertex + j];
    }

    bool connected(int i, int j) const;
};

template <typename V, typename E = int>
struct AdjList : public BaseGraph<V,E>
{
    struct ArcNode
    {
        int id;
        E   weight;
        ArcNode * next;
    };

    ArcNode ** arc_heads;

    AdjList() : BaseGraph<V,E>(), arc_heads(NULL) {}
    ~AdjList() { delete[] arc_heads; }

    typedef V vertex_t;
    typedef E weight_t;
};

template <typename T>
struct WeightTraits
{
    static T infinity()
    {
        return std::numeric_limits<T>::max();
    }

    static T zero()
    {
        return static_cast<T>(0);
    }
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

template <typename V, typename E>
int index_of(const BaseGraph<V,E> * g, const V & v);

// ---------------------------------------------------------------------

template <typename V, typename E>
int index_of(const BaseGraph<V,E> * g, const V & v)
{
    int i = 0;
    for (; i < g->num_vertex; ++i) {
        if (g->vertex[i] == v) {
            break;
        }
    }
    return (i < g->num_vertex) ? i : -1;
}

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
    am->type = type;
    am->num_vertex = num_vertex;
    am->num_edges = num_edges;
    am->vertex = new V[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        am->vertex[i] = V();
    }

    int total = num_vertex * num_vertex;
    E * edges = new E[total];
    for (int i = 0; i < num_vertex; ++i) {
        for (int j = 0; j < num_vertex; ++j) {
            if (j != i) {
                if (is_weighted(type)) {
                    edges[i * num_vertex + j] = WeightTraits<E>::infinity();
                } else {
                    edges[i * num_vertex + j] = WeightTraits<E>::zero();
                }
            } else {
                edges[i * num_vertex + j] = WeightTraits<E>::zero();
            }
        }
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

template <typename V, typename E>
bool AdjMatrix<V,E>::connected(int i, int j) const
{
    return is_weighted(this->type) 
        ? this->e(i,j) != WeightTraits<E>::infinity()
        : this->e(i,j) != WeightTraits<E>::zero();
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
    if (t == WeightTraits<T>::infinity()) {
        return out << std::setw(10) << '*';
    } else {
        return out << std::setw(10) << t;
    }
}

inline std::ostream & output(std::ostream & out, double d)
{
    if (d == std::numeric_limits<double>::max()) {
        return out << std::setw(10) << '*';
    } else {
        return out << std::setprecision(4) << std::setw(10) << d;
    }
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

    output(out, ' ');
    for (int i = 0; i < am->num_vertex; ++i) {
        output(out, am->vertex[i]);
    }
    out << '\n';

    for (int i = 0; i < am->num_vertex; ++i) {
        output(out, am->vertex[i]);
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
    delete am;
}

template <typename V, typename E>
AdjList<V,E> * adj_list_read(std::istream & in, GraphType type)
{
    int num_vertex, num_edges;
    if (!(in >> num_vertex >> num_edges)) {
        return NULL;
    } else if (num_vertex <= 0 || num_edges < 0) {
        return NULL;
    }

    AdjList<V,E> * a = new AdjList<V,E>;
    a->type = type;
    a->num_vertex = num_vertex;
    a->num_edges = num_edges;

    std::map<V,int> v_map;
    V * vertex_list = new V[num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        in >> vertex_list[i];
        v_map[vertex_list[i]] = i;
    }
    a->vertex = vertex_list;

    typedef typename AdjList<V,E>::ArcNode arc_node;
    a->arc_heads = new arc_node* [num_vertex];
    for (int i = 0; i < num_vertex; ++i) {
        a->arc_heads[i] = NULL;
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

        int index1 = v_map[v1];
        int index2 = v_map[v2];
        arc_node * an = new arc_node;
        an->id = index2;
        an->weight = e;
        an->next = a->arc_heads[index1];
        a->arc_heads[index1] = an;

        if (!is_directed(type)) {
            an = new arc_node;
            an->id = index1;
            an->weight = e;
            an->next = a->arc_heads[index2];
            a->arc_heads[index2] = an;
        }
    }

    return a;
}

template <typename V, typename E>
std::ostream & operator<< (std::ostream & out, const AdjList<V,E> * a)
{
    out << "type:   " << type_to_string(a) << '\n';
    out << "vertex: " << a->num_vertex << '\n';
    out << "edges:  " << a->num_edges << '\n';
    for (int i = 0; i < a->num_vertex; ++i) {
        out << '[' << i << ']' << a->vertex[i] << "  ";
    }
    out << '\n';

    typedef typename AdjList<V,E>::ArcNode arc_t;
    for (int i = 0; i < a->num_vertex; ++i) {
        int arc_count = 0;
        const arc_t * p = a->arc_heads[i];
        while (p != NULL) {
            out << '(' << a->vertex[i] << " -> " << a->vertex[p->id] << ')' << '[' << p->weight << ']' << "  ";
            p = p->next;
            ++arc_count;
        }
        if (arc_count > 0) {
            out << '\n';
        }
    }

    return out;
}

template <typename V, typename E>
void graph_destroy(AdjList<V,E> * a)
{
    delete a;
}

#endif
