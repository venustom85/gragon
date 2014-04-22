/*
   p291 9－2－11

   非递归方式深度优先遍历图
  */
#include "common/graph.h"
#include <stack>
#include <cstring>
using namespace std;

namespace exb_9_2_11 {

typedef AdjList<char,int> graph_t;
typedef typename graph_t::ArcNode arc_t;

void dfs(graph_t * g)
{
    if (g == NULL) {
        return;
    }

    stack<arc_t*> stk;
    int * visited = (int*)memset(new int[g->num_vertex], 0, sizeof(int) * g->num_vertex);

    for (int i = 0; i < g->num_vertex; ++i) {
        if (visited[i]) {
            continue;
        }

        cout << g->vertex[i] << endl;
        visited[i] = 1;
        stk.push(g->arc_heads[i]);
        while (!stk.empty()) {
            arc_t * & t = stk.top();
            if (t == NULL) {
                stk.pop();
            } else if (!visited[t->id]) {
                cout << g->vertex[t->id] << endl;
                visited[t->id] = 1;
                stk.push(g->arc_heads[t->id]);
            } else {
                t = t->next;
            }
        }
    }

    delete[] visited;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<char>(cin, DIGRAPH);
    if (g == NULL) {
        cerr << "UNABLE read graph" << endl;
        return 1;
    }

    cout << "graph: \n" << g << endl;

    dfs(g);
    graph_destroy(g);
    return 0;
}

} // namespace exb_9_2_11

