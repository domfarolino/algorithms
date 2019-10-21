#include <vector>
#include <unordered_set>

using Graph = std::vector<std::unordered_set<int>>;
using VisitSet = std::unordered_set<int>;

std::vector<int> topologicalSort(int n, std::vector<std::vector<int>>& prereqs) {
  Graph graph(n, std::unordered_set<int>());
  for (auto entry: prereqs) {
    graph[entry[0]].insert(entry[1]);
  }

  // Graph has been built: {course: <prereq, prereq, ...>}.
  // Need to DFT on the graph. If ever the DFT fails, we
  // must fail. Otherwise, it is OK.
  VisitSet perm_visit, tmp_visit;
  std::vector<int> final_order;
  for (int i = 0; i < graph.size(); ++i) {
    if (!visit(i, graph, perm_visit, tmp_visit, final_order))
      return {};
  }

  return final_order;
}

bool visit(int node, const Graph& graph, VisitSet& perm_visit, VisitSet& tmp_visit, std::vector<int>& final_order) {
  if (perm_visit.find(node) != perm_visit.end())
    return true;
  if (tmp_visit.find(node) != tmp_visit.end())
    return false;

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

int main() {
  // ...
  return 0;
}
