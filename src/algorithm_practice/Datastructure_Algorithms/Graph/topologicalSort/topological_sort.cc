#include <iostream>
#include <vector>
#include <unordered_set>

using Graph = std::vector<std::unordered_set<int>>;
using VisitSet = std::unordered_set<int>;

bool visit(int node, const Graph& graph, VisitSet& perm_visit,
           VisitSet& tmp_visit, std::vector<int>& final_order) {
  if (perm_visit.find(node) != perm_visit.end())
    return true;
  if (tmp_visit.find(node) != tmp_visit.end())
    return false; // Cycle!

  tmp_visit.insert(node);
  for (int i: graph[node]) {
    if (!visit(i, graph, perm_visit, tmp_visit, final_order))
      return false;
  }

  tmp_visit.erase(node);
  final_order.push_back(node);
  perm_visit.insert(node);
  return true;
}

std::vector<int> topological_sort(int num_nodes, std::vector<std::vector<int>>& adjacency_list) {
  Graph graph(num_nodes, std::unordered_set<int>());
  for (auto entry: adjacency_list) {
    graph[entry[0]].insert(entry[1]);
  }

  // Graph has been built: {node: <dependency, dependency, ...>}.
  // Need to DFT on the graph. If ever the DFT fails, we
  // must fail, as this indicates a cycle has been found.
  VisitSet perm_visit, tmp_visit;
  std::vector<int> final_order;
  for (int i = 0; i < graph.size(); ++i) {
    if (!visit(i, graph, perm_visit, tmp_visit, final_order))
      return {};
  }

  return final_order;
}

int main() {
  // TODO(#74): Replace this with our implementation of a directed graph.
  /**
  0 -> {1}
  1 -> {2, 3}
  2 -> {5, 6}
  3 -> {4}
  4 -> {5, 6}
  5 -> {}
  6 -> {5}
 */
  std::vector<std::vector<int>> adjacency_list = {{0, 1}, {1, 2}, {1, 3},
                                                  {2, 5}, {2, 6}, {3, 4},
                                                  {4, 5}, {4, 6}, {6, 5}};

  std::vector<int> final_order = topological_sort(7 /* num_nodes */, adjacency_list);

  std::cout << "Topological ordering: " << std::endl;
  for (int& n: final_order)
    std::cout << n << ", ";
  std::cout << std::endl;

  return 0;
}
