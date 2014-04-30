/*
   Critical Path
  */
#include "common/graph.h"
#include <queue>
#include <stack>
#include <cstring>
#include "common/array_ptr.h"
using namespace std;

namespace exb_9_critpath2 {

typedef char vex_t;
typedef int cost_t;
typedef AdjList<vex_t, cost_t> graph_t;
typedef typename graph_t::ArcNode arc_t;

void print_all_critical_path(const graph_t * g)
{
    if (g == NULL) {
        return;
    }

    const int N = g->num_vertex;

    array_ptr<int> indeg(new int[N]);
    memset(indeg, 0, sizeof(int) * N);

    for (int i = 0; i < N; ++i) {
        for (arc_t * p = g->arc_heads[i]; p != NULL; p = p->next) {
            ++indeg[p->id];
        }
    }

    queue<int> qu;
    int start = -1;
    for (int i = 0; i < N; ++i) {
        if (!indeg[i]) {
            qu.push(i);
            start = i;
        }
    }

    if (start == -1) {
        cerr << "NO start point" << endl;
        return;
    }

    array_ptr<cost_t> E(new cost_t[N]);
    for (int i = 0; i < N; ++i) {
        E[i] = WeightTraits<cost_t>::zero();
    }

    stack<int> path_stk;
    while (!qu.empty()) {
        int s = qu.front();
        path_stk.push(s);
        qu.pop();
        for (arc_t * p = g->arc_heads[s]; p != NULL; p = p->next) {
            cost_t cost = E[s] + p->weight;
            if (cost > E[p->id]) {
                E[p->id] = cost;
            }

            if (!--indeg[p->id]) {
                qu.push(p->id);
            }
        }
    }

    array_ptr<cost_t> L(new cost_t[N]);
    for (int i = 0; i < N; ++i) {
        L[i] = E[path_stk.top()];
    }

    while (!path_stk.empty()) {
        int k = path_stk.top();
        path_stk.pop();
        for (arc_t * p = g->arc_heads[k]; p != NULL; p = p->next) {
            cost_t cost = L[p->id] - p->weight;
            if (cost < L[k]) {
                L[k] = cost;
            }
        }
    }

    int total = N * N;
    array_ptr<int> mat(new int[total]);
    memset(mat, 0, sizeof(int) * total);
    for (int i = 0; i < N; ++i) {
        for (arc_t * p = g->arc_heads[i]; p != NULL; p = p->next) {
            cost_t early = E[i];
            cost_t late = L[p->id] - p->weight;
            if (early == late) {
                mat[i * N + p->id] = 1;  // record a critical activity
            }
        }
    }

    void print_path(const graph_t *, const int *, int);
    print_path(g, mat, start);
}

void print_path_dfs(const graph_t * g, const int * mat, int * visited, int start, int * path, int p)
{
    visited[start] = 1;
    path[p] = start;

    int out_degree = 0;
    const int N = g->num_vertex;
    for (int i = 0; i < N; ++i) {
        if (mat[start * N + i]) {
            ++out_degree;
            if (!visited[i]) {
                print_path_dfs(g, mat, visited, i, path, p + 1);
            }
        }
    }

    visited[start] = 0;

    if (!out_degree) {
        for (int i = 0; i <= p; ++i) {
            cout << g->vertex[path[i]] << ' ';
        }
        cout << endl;
    }
}

void print_path(const graph_t * g, const int * mat, int start)
{
    const int N = g->num_vertex;
    array_ptr<int> path(new int[N]);
    array_ptr<int> visited(new int[N]);
    memset(visited, 0, sizeof(int) * N);
    print_path_dfs(g, mat, visited, start, path, 0);
}

int g_main(int argc, char ** argv)
{
    graph_t * g = NULL;
    while ((g = adj_list_read<vex_t, cost_t>(cin, DINET)) != NULL) {
        cout << g << endl;
        print_all_critical_path(g);
        graph_destroy(g);
        cout << "\n===========================================\n";
    }
}

} // namespace exb_9_critpath2

