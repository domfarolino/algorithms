#include <cstdio>
#include <bitset>
#include <vector> 
using namespace std;

/**
 * 11902 - Dominator UVA problem
 * Description problem: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3053
 */

#define MAX 100
bitset<MAX> status_initial, status_etapa;

/**
 * This dfs will jump the node 'u' when it's equal to 'jump' node.
 */
void dfs(int u, int jump, vector<vector<int>> adjacent_list, bool initial) {
    if (u == jump)
        return;

    bitset<MAX> * visited;
    if (initial) visited = &status_initial;
    else visited = &status_etapa;

    visited->set(u);

    for (int i = 0; i < (int) adjacent_list[u].size(); i++) {
        int v = adjacent_list[u][i];
        if (!visited->test(v)) dfs(v, jump, adjacent_list, initial);
    }
}

/**
 * Method to print the final result.
 */
void print_result(const vector<vector<int>> &adjacent_list, bool initial, int nodes) {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) status_etapa.reset(j);

        dfs(0, i, adjacent_list, initial);

        printf("\n+");
        for (int j = 0; j < nodes * 2 - 1; j++) printf("-");

        printf("+\n|");
        for (int j = 0; j < nodes; j++) {
            if (i == j || !status_etapa.test(j)) {
                if (status_initial.test(j)) printf("Y|");
            } else printf("N|");
        }
    }
    printf("\n+");
    for (int j = 0; j < nodes * 2 - 1; j++) {
        printf("-");
    }
    printf("+\n");
}

int main() {
    int nb_nodes, nb_cases;
    int count = 1;

    vector<vector<int>> adjacent_list;

    // read cases number
    scanf("%d", &nb_cases);

    while (nb_cases--) {
        bool initial = true;
        scanf("%d", &nb_nodes);
        adjacent_list.assign(nb_nodes, vector<int>());
        for (int i = 0; i < nb_nodes; i++) {
            for (int j = 0; j < nb_nodes; j++) {
                int new_edge;
                scanf("%d", &new_edge);
                if (new_edge)
                    adjacent_list[i].push_back(j);
            }
        }

        for (int i = 0; i < nb_nodes; i++)
            status_initial.reset(i);

        dfs(0, nb_nodes, adjacent_list, initial);
        initial = false;

        printf("Case %d:", count++);

        print_result(adjacent_list, initial, nb_nodes);
    }
    return 0;
}
