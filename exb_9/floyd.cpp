/*
   Floyd算法实现
  */
#include "common/graph.h"
#include <stack>
using namespace std;

namespace exb_9_floyd {

typedef char vex_t;
typedef int weight_t;
typedef AdjList<vex_t, weight_t> graph_t;
typedef graph_t::ArcNode arc_t;

struct FI
{
    int prev;
    weight_t cost;
};

void floyd(const graph_t * g)
{
    if (g == NULL || g->num_vertex <= 0) {
        return;
    }

    const int N = g->num_vertex;
    const weight_t INF = numeric_limits<weight_t>::max();
    
    FI * fi = new FI[N*N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fi[i * N + j].cost = INF;
            fi[i * N + j].prev = -1;
        }
    }

    for (int i = 0; i < N; ++i) {
        arc_t * p = g->arc_heads[i];
        while (p != NULL) {
            fi[i * N + p->id].cost = p->weight;
            fi[i * N + p->id].prev = i;
            p = p->next;
        }
    }

    for (int u = 0; u < N; ++u) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) {
                    continue;
                }
                weight_t & iu = fi[i * N + u].cost;
                weight_t & uj = fi[u * N + j].cost;
                weight_t & ij = fi[i * N + j].cost;
                if (iu < INF && uj < INF && iu + uj < ij) {
                    ij = iu + uj;
                    fi[i * N + j].prev = u;
                }
            }
        }
    }

    stack<int> stk;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            FI * fin = &fi[i * N];
            int k = fin[j].prev;
            while (k != -1) {
                stk.push(k);
                k = fin[k].prev;
            }

            if (stk.size() > 0) {
                while (!stk.empty()) {
                    cout << g->vertex[stk.top()] << ' ';
                    stk.pop();
                }
                cout << g->vertex[j] << endl;
            }
        }
    }

    delete[] fi;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_list_read<vex_t, weight_t>(cin, DINET);
    cout << g << endl;
    floyd(g);
    graph_destroy(g);
    return 0;
}

} // namespace exb_9_floyd

