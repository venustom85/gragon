/*
   Dijkstra算法实现
  */
#include "common/graph.h"
#include <cstring>
#include <stack>
using namespace std;

namespace exb_9_dijkstra {

typedef int weight_t;
typedef AdjList<char,weight_t> graph_t;
typedef typename graph_t::ArcNode arc_node_t;

struct Dist
{
    int v;
    int prev;
    weight_t cost;
};

void print_shortest_path(const graph_t * g, char s)
{
    if (g == NULL) {
        return;
    }

    int s_i = index_of(g, s);
    if (s_i < 0) {
        cerr << "ERROR vertex" << endl;
        return;
    }

    Dist * dist = new Dist[g->num_vertex];
    int * selected = new int[g->num_vertex];
    memset(selected, 0, sizeof(int) * g->num_vertex);
    for (int i = 0; i < g->num_vertex; ++i) {
        dist[i].v = i;
        dist[i].cost = numeric_limits<weight_t>::max();
        dist[i].prev = -1;
    }
    selected[s_i] = 1; 

    arc_node_t * p = g->arc_heads[s_i];
    while (p != NULL) {
        int v = p->id;
        dist[v].cost = p->weight;
        dist[v].prev = s_i;
        p = p->next;
    }

    int u_count = g->num_vertex - 1;
    while (u_count > 0) {
        weight_t min = numeric_limits<weight_t>::max();
        int min_i = -1;
        for (int i = 0; i < g->num_vertex; ++i) {
            if (!selected[i] && dist[i].cost < min) {
                min_i = i;
                min = dist[i].cost;
            }
        }

        if (min_i == -1) {
            cerr << "NOT a connected graph!" << endl;
            return;
        }

        selected[min_i] = 1;

        p = g->arc_heads[min_i];
        while (p != NULL) {
            int v = p->id;
            if (!selected[v] && min + p->weight < dist[v].cost) {
                dist[v].cost = min + p->weight;
                dist[v].prev = min_i;
            }
            p = p->next;
        }

        --u_count;
    }

    stack<int> stk;
    for (int i = 0; i < g->num_vertex; ++i) {
        if (i != s_i) {
            int j = i;
            while (j != -1) {
                stk.push(j);
                j = dist[j].prev;
            }

            while (!stk.empty()) {
                cout << stk.top() << ' ';
                stk.pop();
            }
            cout << endl;
        }
    }

    delete[] selected;
    delete[] dist;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<char,weight_t>(cin, DINET);
    cout << g << endl;

    char s = '#';
    cin >> s;
    cout << "start point: " << s << endl;

    print_shortest_path(g, s);

    graph_destroy(g);

    return 0;
}

} // namespace exb_9_dijkstra

