/*
   Kruskal算法
  */
#include <cstring>
#include "common/graph.h"
using namespace std;

namespace exb_9_kruskal {

typedef int weight_t;
typedef AdjList<char,weight_t> graph_t;
typedef typename graph_t::ArcNode arc_node_t;

struct Edge
{
    int a, b;
    weight_t weight;
};

int find_parent(int * parents, int i)
{
    int p = i;
    while (parents[p] >= 0) {
        p = parents[p];
    }

    int t, k = i;
    while (parents[k] >= 0 && parents[k] != p) {
        t = parents[k];
        parents[k] = p;
        k = t;
    }

    return p;
}

int merge(int * parents, int i, int j)
{
    if (parents[i] > parents[j]) {
        parents[j] += parents[i];
        parents[i] = j;
        return j;
    } else {
        parents[i] += parents[j];
        parents[j] = i;
        return i;
    }
}

void kruskal(const graph_t * g)
{
    if (g == NULL) {
        return;
    }

    Edge * edges = new Edge[g->num_edges];
    int e = 0;
    for (int i = 0; i < g->num_vertex; ++i) {
        arc_node_t * p = g->arc_heads[i];
        while (p != NULL) {
            if (i < p->id) {
                edges[e].a = i;
                edges[e].b = p->id;
                edges[e].weight = p->weight;
                ++e;
            }
            p = p->next;
        }
    }

    int * parents = new int[g->num_vertex];
    for (int i = 0; i < g->num_vertex; ++i) {
        parents[i] = -1;
    }

    int e_count = 0;
    int e_end = g->num_edges;
    int max_e = g->num_vertex - 1;
    while (e_count < max_e && e_end > 0) {
        weight_t min = numeric_limits<weight_t>::max();
        int min_i = -1;
        for (int i = 0; i < e_end; ++i) {
            if (edges[i].weight < min) {
                min_i = i;
                min = edges[i].weight;
            }
        }
        int pa = find_parent(parents, edges[min_i].a);
        int pb = find_parent(parents, edges[min_i].b);
        if (pa != pb) {
            cout << edges[min_i].a << " -- " << edges[min_i].b << endl;
            merge(parents, pa, pb);
            ++e_count;
        }

        if (min_i < e_end - 1) {
            Edge temp = edges[min_i];
            edges[min_i] = edges[e_end - 1];
            edges[e_end - 1] = temp;
        }
        --e_end;
    }

    if (e_count < max_e) {
        cerr << "NOT a connected graph" << endl;
    }

    delete[] parents;
    delete[] edges;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<char,weight_t>(cin, UNDINET);
    cout << g << endl;

    kruskal(g);
    graph_destroy(g);
    return 0;
}

} // namespace exb_9_kruskal

