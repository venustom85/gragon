/*
   p320 9-4-9

   偏心度是有向图G中除v外所有顶点到v最短路径的最大值，具有最小偏心度的顶点称为有向图的中心点。
  */
#include "common/graph.h"
#include "common/array_ptr.h"
using namespace std;

namespace exb_9_4_9 {

typedef char vex_t;
typedef int cost_t;
typedef AdjMatrix<vex_t, cost_t> graph_t;

vex_t get_center(const graph_t * g)
{
    if (g == NULL) {
        return vex_t(-1);
    }

    const int N = g->num_vertex;
    const cost_t INF = WeightTraits<cost_t>::infinity();
    array_ptr<cost_t> mat(new cost_t[N * N]);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[i * N + j] = g->e(i,j);
        }
    }

    for (int u = 0; u < N; ++u) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j || u == i || u == j) {
                    continue;
                }

                cost_t & iu = mat[i * N + u];
                cost_t & uj = mat[u * N + j];
                cost_t & ij = mat[i * N + j];
                if (iu < INF && uj < INF && iu + uj < ij) {
                    ij = iu + uj;
                }
            }
        }
    }

    cost_t min = INF;
    int min_i = -1;
    for (int i = 0; i < N; ++i) {
        cost_t max = 0;
        for (int j = 0; j < N; ++j) {
            cost_t v = mat[j * N + i];
            if (v > max) {
                max = v;
            }
        }

        cout << "max mindist of " << g->vertex[i] << " is " << max << endl;

        if (max < min) {
            min = max;
            min_i = i;
        }
    }

    return g->vertex[min_i];
}

int g_main(int argc, char ** argv)
{
    graph_t * g = NULL;
    while ((g = adj_matrix_read<vex_t, cost_t>(cin, DINET)) != NULL) {
        cout << g << endl;
        vex_t center = get_center(g);
        if (center != -1) {
            cout << "center point is " << center << endl;
        } else {
            cout << "NO center point found" << endl;
        }
        graph_destroy(g);
    }
    return 0;
}

} // namespace exb_9_4_9

