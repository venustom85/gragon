/*
   实现prim算法
  */
#include "common/graph.h"
using namespace std;

namespace exb_9_prim {

typedef AdjMatrix<char,double> graph_t;

struct Edge
{
    int a;
    int b;
};

struct WeightedEdge
{
    int selected;
    int unselected;
    double cost;
};

bool prim(const graph_t * g, Edge * edges)
{
    if (g == NULL || edges == NULL) {
        return false;
    }

    WeightedEdge * we = new WeightedEdge[g->num_vertex - 1];
    for (int i = 1; i < g->num_vertex; ++i) {
        we[i-1].selected = 0;
        we[i-1].unselected = i;
        we[i-1].cost = g->edges[i];
    }

    int s = g->num_vertex - 1;
    int ep = 0;
    while (s > 0) {
        double min = numeric_limits<double>::max();
        int min_i = -1;
        for (int i = 0; i < s; ++i) {
            if (we[i].cost < min) {
                min = we[i].cost;
                min_i = i;
            }
        }
        if (min_i == -1) {
            delete[] we;
            return false;
        }

        edges[ep].a = we[min_i].selected;
        edges[ep].b = we[min_i].unselected;
        ++ep;

        int new_v = we[min_i].unselected;
        if (min_i != s - 1) {
            WeightedEdge temp = we[min_i];
            we[min_i] = we[s - 1];
            we[s - 1] = temp;
        }
        --s;

        for (int i = 0; i < s; ++i) {
            int u = we[i].unselected;
            double cost = g->edges[new_v * g->num_vertex + u];
            if (cost < we[i].cost) {
                we[i].cost = cost;
                we[i].selected = new_v;
            }
        }
    }

    delete[] we; 

    return true;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_matrix_read<char,double>(cin, UNDINET);
    cout << g << endl;

    Edge * ed = new Edge[g->num_vertex - 1];
    if (prim(g, ed)) {
        for (int i = 0; i < g->num_vertex - 1; ++i) {
            cout << ed[i].a << ' ' << ed[i].b << endl;
        }
    } else {
        cerr << "NOT a connected graph" << endl;
    }
    delete[] ed;
    graph_destroy(g);

    return 0;
}

} // namespace exb_9_prim

