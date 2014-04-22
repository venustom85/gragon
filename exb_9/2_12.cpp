/*
   p291 9-2-12

   求图中距v最远的节点
  */
#include "common/graph.h"
#include <queue>
#include <cstring>
using namespace std;

namespace exb_9_2_12 {

typedef AdjList<char,int> graph_t;
typedef typename graph_t::ArcNode arc_t;

char farest(const graph_t * g, char v)
{
    if (g == NULL) {
        return -1;
    }

    int i = 0;
    for (; i < g->num_vertex; ++i) {
        if (g->vertex[i] == v) {
            break;
        }
    }
    if (i == g->num_vertex) {
        return -1;
    }

    int * visited = new int[g->num_vertex];
    memset(visited, 0, sizeof(int) * g->num_vertex);

    int far = -1;
    queue<int> qu;
    qu.push(i);
    visited[i] = 1;
    while (!qu.empty()) {
        far = qu.front();
        qu.pop();
        arc_t * p = g->arc_heads[far];
        while (p != NULL) {
            if (!visited[p->id]) {
                visited[p->id] = 1;
                qu.push(p->id);
            }
            p = p->next;
        }
    }

    delete[] visited;

    return g->vertex[far];
}

int g_main(int argc, char ** argv)
{
    AdjList<char> * g = adj_list_read<char>(cin, UNDIGRAPH);
    cout << "graph: \n" << g << endl;

    char start;
    cin >> start;
    cout << "start node: " << start << endl;

    char farest_node = farest(g, start);
    cout << farest_node << " is farest node" << endl;

    return 0;
}

} // namespace exb_9_2_12

