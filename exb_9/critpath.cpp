/*
   Critical Path
  */
#include "common/graph.h"
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

namespace exb_9_critpath {

typedef char vex_t;
typedef int cost_t;
typedef AdjList<vex_t, cost_t> graph_t;
typedef graph_t::ArcNode arc_t;

void 
print_all_dfs(const graph_t * g, int start, int * visited, const int * mat, int * path, int p)
{
    visited[start] = 1;
    path[p] = start;

    int c = 0;
    for (int i = 0; i < g->num_vertex; ++i) {
        if (mat[start * g->num_vertex + i]) {
            if (!visited[i]) {
                print_all_dfs(g, i, visited, mat, path, p + 1);
            }
            ++c;
        }
    }

    if (c == 0) {
        for (int i = 0; i <= p; ++i) {
            cout << g->vertex[path[i]] << ' ';
        }
        cout << endl;
    }

    visited[start] = 0;
}

void print_all(const graph_t * g, int start, const int * mat, int * path)
{
    int * visited = new int[g->num_vertex];
    memset(visited, 0, sizeof(int) * g->num_vertex);

    print_all_dfs(g, start, visited, mat, path, 0);

    delete[] visited;
}

void print_all_critical_path(const graph_t * g)
{
    if (g == NULL) {
        return;
    }

    const int N = g->num_vertex;
    int * indeg = new int[N];
    memset(indeg, 0, sizeof(int) * N);
    for (int i = 0; i < N; ++i) {
        arc_t * p = g->arc_heads[i];
        while (p != NULL) {
            ++indeg[p->id];
            p = p->next;
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
        cerr << "NO start point!" << endl;
        return;
    }

    stack<int> rev_seq;
    cost_t * E = new cost_t[N];
    memset(E, 0, sizeof(int) * N);
    cost_t max_cost = WeightTraits<cost_t>::zero();
    while (!qu.empty()) {
        int s = qu.front();
        rev_seq.push(s);
        qu.pop();
        arc_t * p = g->arc_heads[s];
        while (p != NULL) {
            --indeg[p->id];
            if (!indeg[p->id]) {
                qu.push(p->id);
            }
            if (E[p->id] < E[s] + p->weight) {
                E[p->id] = E[s] + p->weight;
                if (max_cost < E[p->id]) {
                    max_cost = E[p->id];
                }
            }
            p = p->next;
        }
    }

    cost_t * L = new cost_t[N];
    for (int i = 0; i < N; ++i) {
        L[i] = max_cost;
    }
    while (!rev_seq.empty()) {
        int t = rev_seq.top();
        rev_seq.pop();
        arc_t * p = g->arc_heads[t];
        while (p != NULL) {
            if (L[t] > L[p->id] - p->weight) {
                L[t] = L[p->id] - p->weight;
            }
            p = p->next;
        }
    }

    int total = N * N;
    int * mat = new int[total];
    memset(mat, 0, sizeof(int) * total);
    for (int i = 0; i < N; ++i) {
        for (arc_t * p = g->arc_heads[i]; p != NULL; p = p->next) {
            cost_t ve = E[i];
            cost_t vl = L[p->id] - p->weight;
            if (ve == vl) {
                mat[i * N + p->id] = 1;
            }
        }
    }

    int * path = new int[N];
    print_all(g, start, mat, path);

    delete[] path;
    delete[] mat;
    delete[] indeg;
    delete[] E;
    delete[] L;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = NULL;

    while ((g = adj_list_read<vex_t, cost_t>(cin, DINET)) != NULL) {
        cout << g << endl;
        print_all_critical_path(g);
        graph_destroy(g);
        cout << "\n==============================================\n";
    }

    return 0;
}

} // namespace exb_9_critpath

