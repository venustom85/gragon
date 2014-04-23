/*
   p294 9-2-16

   输出所有u到v所有长度为L的简单路径
  */
#include "common/graph.h"
#include <stack>
#include <cstring>
using namespace std;

namespace exb_9_2_16 {

typedef AdjList<char> graph_t;
typedef typename graph_t::ArcNode arc_node_t;

void all_path(const graph_t * g, int * visited, int k, int v, int L, char * path, int p)
{
    if (k == v && p == L) {
        for (int i = 0; i < p; ++i) {
            cout << path[i] << ' ';
        }
        cout << g->vertex[k] << endl;
        return;
    } else if (p > L) {
        return;
    }

    path[p] = g->vertex[k];
    visited[k] = 1;
    
    arc_node_t * ap = g->arc_heads[k];
    while (ap != NULL) {
        if (!visited[ap->id]) {
            all_path(g, visited, ap->id, v, L, path, p + 1);
        }
        ap = ap->next;
    }

    visited[k] = 0;
}

void from_u_to_v(const graph_t * g, char u, char v, int L)
{
    if (g == NULL) {
        return ;
    }

    int i = index_of(g, u);
    int j = index_of(g, v);

    if (i == -1 || j == -1) {
        return;
    }

    int * visited = new int[g->num_vertex];
    memset(visited, 0, sizeof(int) * g->num_vertex);

    char * path = new char[g->num_vertex - 1];

    all_path(g, visited, i, j, L, path, 0);

    delete[] path;
    delete[] visited;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<char>(cin, UNDIGRAPH);
    cout << g << endl;

    char u, v;
    int L;
    cin >> u >> v >> L;
    if (!cin) {
        cerr << "UNABLE to read u, v, L" << endl;
        return 1;
    }

    from_u_to_v(g, u, v, L);

    graph_destroy(g);

    return 0;
}

} // namespace exb_9_2_16

