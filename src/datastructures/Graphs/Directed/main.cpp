#include <iostream>

#include "Graph.h"

int main() {
  int numVertices, numEdges = 1, edgeV1, edgeV2;

  std::cout << "Input the number of vertices in the graph" << std::endl;
  std::cin >> numVertices;

  Graph graph(numVertices);

  while (1) {
    std::cout << "Input both vertices for edge #" << numEdges << " or -1 to stop" << std::endl;

    std::cin >> edgeV1;
    if (edgeV1 < 0) break;

    std::cin >> edgeV2;

    graph.AddEdge(edgeV1, edgeV2);
    numEdges++;
  }

  // Use the graph!

  std::vector<int> bfs = graph.BFS(0);
  std::cout << "Printing DFS: " << std::endl;
  std::vector<int> dfs = graph.DFS(0);

  for (int i = 0; i < dfs.size(); ++i) {
    std::cout << dfs[i] << " -> ";
    if (i + 1 == dfs.size()) std::cout << std::endl;
  }

  std::cout << "Printing BFS: " << std::endl;

  for (int i = 0; i < dfs.size(); ++i) {
    std::cout << bfs[i] << " -> ";
    if (i + 1 == dfs.size()) std::cout << std::endl;
  }

  int diameter = graph.Diameter();

  graph.PrintAdjacencyMatrix();
  graph.PrintDistanceMatrix();

  if (diameter < 0) {
    std::cout << "Graph is disconnected" << std::endl;
  } else {
    std::cout << "Graph is connected with diameter " << diameter << std::endl;
  }

  graph.PrintComponents();

  std::cout << graph.ShortestPath(0, 3) << std::endl;
  return 0;
}
