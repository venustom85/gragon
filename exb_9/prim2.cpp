/*
   Prim
  */
#include "common/graph.h"
using namespace std;

namespace exb_9_prim2 {

typedef int weight_t;

typedef AdjMatrix<char,weight_t> graph_t;

struct PrimCell
{
    int src;
    int flag;
    weight_t cost;
};

void prim(const graph_t * g)
{
    if (g == NULL) {
        return;
    } else if (g->num_vertex <= 0) {
        return;
    }

    const int N = g->num_vertex;
    PrimCell * pc = new PrimCell[N];
    pc[0].flag = 1;

    for (int i = 1; i < N; ++i) {
        pc[i].src = 0;
        pc[i].cost = g->e(0,i);
        pc[i].flag = 0;
    }

    for (int i = 1; i < N; ++i) {
        weight_t min = numeric_limits<weight_t>::max();
        int min_i = -1;
        for (int j = 1; j < N; ++j) {
            if (!pc[j].flag && pc[j].cost < min) {
                min_i = j;
                min = pc[j].cost;
            }
        }

        if (min_i == -1) {
            cerr << "NOT a connected graph!" << endl;
            return;
        }

        pc[min_i].flag = 1;
        cout << g->vertex[pc[min_i].src] << " -- " << g->vertex[min_i] << endl;

        for (int j = 1; j < N; ++j) {
            if (!pc[j].flag && g->e(min_i,j) < pc[j].cost) {
                pc[j].cost = g->e(min_i,j);
                pc[j].src = min_i;
            }
        }
    }

    delete[] pc;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_matrix_read<char,weight_t>(cin, UNDINET);
    cout << g << endl;

    prim(g);

    graph_destroy(g);

    return 0;
}

} // namespace exb_9_prim2

