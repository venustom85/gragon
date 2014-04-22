/*
   判断无向图是否是一棵树
  */
#include "common/graph.h"
#include <stack>
#include <cstring>
using namespace std;

namespace exb_9_2_13 {

typedef AdjList<char> graph_t;
typedef typename graph_t::ArcNode arc_t;

bool is_tree(const graph_t * g)
{
    if (g == NULL) {
        return true;
    } else if (g->num_vertex == 1) {
        return true;
    }

    int * visited = new int[g->num_vertex];
    memset(visited, 0, sizeof(int) * g->num_vertex);

    stack<arc_t*> stk;
    int v_count = 0, e_count = 0;

    visited[0] = 1;
    if (g->arc_heads[0] == NULL && g->num_vertex > 1) {
        return false;
    }
    ++v_count;
    ++e_count;
    stk.push(g->arc_heads[0]);

    while (!stk.empty()) {
        arc_t * & top = stk.top();
            if (!visited[top->id]) {
                visited[top->id] = 1;
                ++v_count;
                if (g->arc_heads[top->id] != NULL) {
                    ++e_count;
                    stk.push(g->arc_heads[top->id]);
                } 
            } else {
                top = top->next;
                if (top != NULL) {
                    ++e_count;
                } else {
                    stk.pop();
                }
            }
    }

    delete[] visited;

    return (v_count == g->num_vertex) && (e_count / 2 == v_count - 1);
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<char>(cin, UNDIGRAPH);
    cout << "graph: \n" << g << endl;

    bool is_tree_b = is_tree(g);
    if (is_tree_b) {
        cout << "is tree" << endl;
    } else {
        cout << "is not tree" << endl;
    }

    graph_destroy(g);

    return 0;
}

} // namespace exb_9_2_13

