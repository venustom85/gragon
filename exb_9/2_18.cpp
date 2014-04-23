/*
   p295 9-2-18

   图G采用邻接矩阵存储，输出图G中从顶点u到v的所有简单路径。
  */
#include "common/graph.h"
#include <cstring>
using namespace std;

namespace exb_9_2_18 {

typedef AdjMatrix<char> graph_t;

void find_all_path(const graph_t * g, int * visited, int s, int v, char * path, int p)
{
    if (s == v) {
        for (int i = 0; i < p; ++i) {
            cout << path[i] << ' ';
        }
        cout << g->vertex[s] << endl;
        return;
    }

    visited[s] = 1;
    path[p] = g->vertex[s];

    for (int col = 0; col < g->num_vertex; ++col) {
        int m = g->edges[s * g->num_vertex + col];
        if (m && !visited[col]) {
            find_all_path(g, visited, col, v, path, p + 1);
        }
    }

    visited[s] = 0;
}

void all_path(const graph_t * g, char u, char v)
{
    if (g == NULL) {
        return;
    }

    int i = index_of(g, u);
    int j = index_of(g, v);
    if (i < 0 || j < 0) {
        return;
    }

    int * visited = new int[g->num_vertex];
    memset(visited, 0, sizeof(int) * g->num_vertex);

    char * path = new char[g->num_vertex - 1];

    find_all_path(g, visited, i, j, path, 0);

    delete[] visited;
    delete[] path;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_matrix_read<char>(cin, UNDIGRAPH);
    cout << g << endl;

    char u, v;
    cin >> u >> v;
    if (!cin) {
        cerr << "UNABLE to read u and v" << endl;
        return 1;
    }

    all_path(g, u, v);

    graph_destroy(g);

    return 0;
}

} // namespace exb_9_2_18

