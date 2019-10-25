#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <unordered_map>

class Graph {
private:
  bool ComputeDistanceMatrix();
  std::unordered_map<int, int> BFSWithDistance(int);
  void DFSHelper(int, std::vector<int>&, std::unordered_set<int>&);

  int size_;
  std::vector<std::vector<bool>> adjacency_matrix_;
  std::vector<std::vector<int>> distance_matrix_;
  bool distance_matrix_computed_;

public:
  Graph(int);

  void addEdge(int, int);
  int shortestPath(int, int);
  int getDiameter();
  std::vector<int> bfs(int);
  std::vector<int> dfs(int);
  void printAdjacencyMatrix();
  void printDistanceMatrix();
  void printComponents();
};

#endif
