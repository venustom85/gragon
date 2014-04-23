/*
   p296 9-2-19

  */
#include "common/graph.h"
#include <cstring>
using namespace std;

namespace exb_9_2_19 {

typedef AdjList<int> graph_t;
typedef typename graph_t::ArcNode arc_node_t;

int includes[] = {7,9};
int excludes[] = {1,6};

bool cond(const int * path, int p)
{
    int in = 0;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (path[i] == includes[j]) {
                ++in;
            }
        }
        for (int j = 0; j < 2; ++j) {
            if (path[i] == excludes[j]) {
                return false;
            }
        }
    }

    return in == 2;
}

void all_path(const graph_t * g, int * visited, int s, int v, int * path, int p)
{
    if (s == v) {
        if (cond(path, p)) {
            for (int i = 0; i < p; ++i) {
                cout << path[i] << ' ';
            }
            cout << g->vertex[s] << endl;
        }
        return;
    }

    visited[s] = 1;
    path[p] = g->vertex[s];

    arc_node_t * ap = g->arc_heads[s];
    while (ap != NULL) {
        if (!visited[ap->id]) {
            all_path(g, visited, ap->id, v, path, p + 1);
        }
        ap = ap->next;
    }

    visited[s] = 0;
}

void find_all_path(const graph_t * g, int u, int v)
{
    if (g == NULL) {
        return;
    }

    int i = index_of(g, u);
    int j = index_of(g, v);

    int * visited = new int[g->num_vertex];
    memset(visited, 0, sizeof(int) * g->num_vertex);

    int * path = new int[g->num_vertex - 1];
    all_path(g, visited, i, j, path, 0);

    delete[] path;
    delete[] visited;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<int>(cin, UNDIGRAPH);
    cout << g << endl;

    int u, v;
    cin >> u >> v;
    if (!cin) {
        cerr << "UNABLE to read u and v" << endl;
        return 1;
    }

    find_all_path(g, u, v);

    graph_destroy(g);

    return 0;
}

} // namespace exb_9_2_19

