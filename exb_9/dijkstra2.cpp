/*
   Dijkstra
  */
#include "common/graph.h"
#include <stack>
using namespace std;

namespace exb_9_dijkstra2 {

typedef int weight_t;
typedef AdjMatrix<char,weight_t> graph_t;

struct Di
{
    int prev;
    weight_t length;
    int flag;
};

void dijkstra(const graph_t * g, char start)
{
    if (g == NULL || g->num_vertex <= 0) {
        return;
    }
    const int N = g->num_vertex;

    int si = -1;
    for (int i = 0; i < N; ++i) {
        if (g->vertex[i] == start) {
            si = i;
            break;
        }
    }
    if (si == -1) {
        cerr << "ERROR start vertex " << start << endl;
        return;
    }

    Di * di = new Di[N];
    for (int i = 0; i < N; ++i) {
        di[i].length = g->e(si, i);
        if (g->connected(si, i)) {
            di[i].prev = si;
        } else {
            di[i].prev = -1;
        }
        di[i].flag = 0;
    }

    di[si].flag = 1;
    di[si].prev = -1;

    for (int i = 0; i < N; ++i) {
        if (i == si) {
            continue;
        }

        weight_t min = numeric_limits<weight_t>::max();
        int mi = -1;
        for (int j = 0; j < N; ++j) {
            if (!di[j].flag && di[j].length < min) {
                mi = j;
                min = di[j].length;
            }
        }

        if (mi == -1) {
            cerr << "NOT a connected graph!" << endl;
            return;
        }

        di[mi].flag = 1;

        for (int j = 0; j < N; ++j) {
            if (!g->connected(mi, j)) {
                continue;
            }
            weight_t cost = g->e(mi, j) + di[mi].length;
            if (!di[j].flag && cost < di[j].length) {
                di[j].length = cost;
                di[j].prev = mi;
            }
        }
    }

    stack<int> stk;
    for (int i = 0; i < N; ++i) {
        int j = i;
        while (j != -1) {
            stk.push(j);
            j = di[j].prev;
        }

        while (!stk.empty()) {
            cout << g->vertex[stk.top()] << ' ';
            stk.pop();
        }
        cout << '\n';
    }

    delete[] di;
}

int g_main(int argc, char ** argv)
{
    graph_t * g = adj_matrix_read<char,weight_t>(cin, DINET);
    cout << g << endl;

    char start;
    cin >> start;
    if (!cin) {
        cerr << "NEED start vertex" << endl;
        return 1;
    }
    cout << "start from " << start << endl;
    dijkstra(g, start);

    graph_destroy(g);

    return 0;
}

} // namespace exb_9_dijkstra2

