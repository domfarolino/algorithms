#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>
#include <unordered_map>

class Graph {
private:
  int numVertices;
  bool **adjacencyMatrix;
  int **distanceMatrix;
  bool distanceMatrixComputed;

  void initAdjacencyMatrix();
  void initDistanceMatrix();

  bool computeDistanceMatrix();
  std::unordered_map<int, int> bfsWithDistance(int);
  void dfsHelper(int, std::vector<int>&, std::unordered_set<int>&);

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

  ~Graph();
};

#endif
