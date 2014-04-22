/*
   DFS
  */
#include "common/graph.h"
#include <stack>
#include <cstring>
using namespace std;

namespace exb_9_dfs {

typedef AdjList<char> graph_t;
typedef typename graph_t::ArcNode arc_node_t;

void dfs(const graph_t * g)
{
    if (g == NULL || g->num_vertex == 0) {
        return;
    }

    int * visited = new int[g->num_vertex];
    memset(visited, 0, sizeof(int) * g->num_vertex);

    stack<arc_node_t*> stk;

    for (int i = 0; i < g->num_vertex; ++i) {
        if (visited[i]) {
            continue;
        }
        cout << g->vertex[i] << endl;
        visited[i] = 1;
        stk.push(g->arc_heads[i]);
        while (!stk.empty()) {
            arc_node_t * & top = stk.top();
            if (top == NULL) {
                stk.pop();
            } else {
                arc_node_t * arc = top;
                top = top->next;
                if (!visited[arc->id]) {
                    cout << g->vertex[arc->id] << endl;
                    visited[arc->id] = 1;
                    stk.push(g->arc_heads[arc->id]);
                }
            }
        }
    }

    delete[] visited;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<char>(cin, UNDIGRAPH);
    cout << g << endl;
    cout << "dfs: " << endl;
    dfs(g);
    graph_destroy(g);
    return 0;
}

} // namespace exb_9_dfs

