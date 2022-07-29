#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <unordered_map>

class directed_graph {
private:
  bool compute_distance_matrix();
  std::unordered_map<int, int> bfs_with_distance(int);
  void dfs_helper(int, std::vector<int>&, std::unordered_set<int>&);

  int size_;
  std::vector<std::vector<bool>> adjacency_matrix_;
  std::vector<std::vector<int>> distance_matrix_;
  bool distance_matrix_computed_;

public:
  directed_graph(int);

  void add_edge(int, int);
  std::vector<int> dfs(int);
  std::vector<int> bfs(int);
  std::vector<std::unordered_map<int, int>> connected_components();
  int shortest_path(int, int);
  int diameter();

  // Printing method.
  void PrintConnectedComponents();
};

#endif // GRAPH_H
