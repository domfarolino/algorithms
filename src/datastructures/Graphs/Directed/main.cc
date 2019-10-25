#include <iostream>

#include "Graph.h"

int main() {
  int vertices, edges = 1, edge_v1, edge_v2;

  std::cout << "Input the number of vertices in the graph" << std::endl;
  std::cin >> vertices;

  Graph graph(vertices);

  while (1) {
    std::cout << "Input both vertices for edge #" << edges++ << " or -1 to stop" << std::endl;

    std::cin >> edge_v1;
    if (edge_v1 < 0) // Quit signal.
      break;

    std::cin >> edge_v2;
    if (edge_v2 < 0)
      throw std::logic_error("Edge vertices must be valid");

    graph.AddEdge(edge_v1, edge_v2);
  }

  // Use the graph!

  // Start with traversals.
  std::vector<int> bfs = graph.BFS(0);
  std::vector<int> dfs = graph.DFS(0);

  std::cout << "Printing DFS: " << std::endl;
  for (int& node: dfs)
    std::cout << node << " -> ";
  std::cout << std::endl;

  std::cout << "Printing BFS: " << std::endl;
  for (int& node: bfs)
    std::cout << node << " -> ";
  std::cout << std::endl;

  // Show an adjacency matrix representation of the graph.
  graph.PrintAdjacencyMatrix();

  // Compute the graph's diameter and distance matrix.
  int diameter = graph.Diameter();
  graph.PrintDistanceMatrix();
  if (diameter < 0)
    std::cout << "Graph is disconnected\n";
  else
    std::cout << "Graph is connected with diameter " << diameter << std::endl;

  // Print the graphs' connected components, if any.
  graph.PrintConnectedComponents();

  std::cout << graph.ShortestPath(0, 3) << std::endl;
  return 0;
}
