/*
   Topological Sort
  */
#include "common/graph.h"
#include <queue>
#include <cstring>
using namespace std;

namespace exb_9_topological {

typedef char vex_t;
typedef AdjList<vex_t> graph_t;
typedef graph_t::ArcNode arc_t;

bool topological_sort(const graph_t * g, vex_t * seq)
{
    if (g == NULL || seq == NULL || g->num_vertex < 0) {
        return false;
    }

    const int N = g->num_vertex;
    queue<int> qu;

    int * indeg = new int[N];
    memset(indeg, 0, sizeof(int) * N);

    for (int i = 0; i < N; ++i) {
        arc_t * p = g->arc_heads[i];
        while (p != NULL) {
            ++indeg[p->id];
            p = p->next;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (!indeg[i]) {
            qu.push(i);
        }
    }

    int s = 0;
    while (!qu.empty()) {
        int k = qu.front();
        qu.pop();

        seq[s++] = g->vertex[k];

        arc_t * p = g->arc_heads[k];
        while (p != NULL) {
            if (!--indeg[p->id]) {
                qu.push(p->id);
            }
            p = p->next;
        }
    }
               
    delete[] indeg;

    return s == N;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<vex_t>(cin, DIGRAPH);
    if (g == NULL) {
        cerr << "UNABLE to read graph" << endl;
        return 1;
    }
    cout << g << endl;

    char * top_seq = new char[g->num_vertex];
    bool result = topological_sort(g, top_seq);
    if (result) {
        for (int i = 0; i < g->num_vertex; ++i) {
            cout << top_seq[i] << ' ';
        }
        cout << endl;
    } else {
        cout << "UNABLE to sort, may be not a connected graph, or there's circular path in it" << endl;
    }

    delete[] top_seq;

    graph_destroy(g);
    return 0;
}

} // namespace exb_9_topological

