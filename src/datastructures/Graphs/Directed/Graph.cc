#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Graph.h"

Graph::Graph(int inNumVertices): numVertices(std::max(inNumVertices, 0)),
                                 adjacencyMatrix(numVertices, std::vector<bool>(numVertices, false)),
                                 distanceMatrix(numVertices, std::vector<int>(numVertices, -1)),
                                 distanceMatrixComputed(false) {}

void Graph::addEdge(int i, int j) {
  if (i < 0 || j < 0 || i >= numVertices || j >= numVertices) {
    std::cerr << "Node for edge is out-of-bounds" << std::endl;
    return;
  }

  adjacencyMatrix[i][j] = true; // Directed edge.
  distanceMatrixComputed = false;
}

std::vector<int> Graph::dfs(int vertex) {
  std::vector<int> returnVec;
  std::unordered_set<int> visited;
  dfsHelper(vertex, returnVec, visited);

  return returnVec;
}

void Graph::dfsHelper(int vertex, std::vector<int> &vec, std::unordered_set<int> &visited) {
  vec.push_back(vertex);
  visited.insert(vertex);

  // Only DFS recurse on unvisited nodes.
  for (int j = 0; j < numVertices; ++j) {
    if (adjacencyMatrix[vertex][j] && visited.find(j) == visited.end()) {
      dfsHelper(j, vec, visited);
    }
  }
}

std::vector<int> Graph::bfs(int vertex) {
  std::vector<int> returnVec;
  std::unordered_set<int> visited;
  std::queue<int> q;

  q.push(vertex);
  visited.insert(vertex);

  while (!q.empty()) {
    returnVec.push_back(q.front());

    // Push all of q.front()'s children.
    for (int j = 0; j < numVertices; ++j) {
      if (adjacencyMatrix[q.front()][j] && visited.find(j) == visited.end()) {
        q.push(j);
        visited.insert(j);
      }
    }

    q.pop();
  }

  return returnVec;
}

std::unordered_map<int, int> Graph::bfsWithDistance(int vertex) {
  std::unordered_map<int, int> visited;
  std::queue<int> q;

  int count, distance = 0;
  q.push(vertex);
  visited.insert({vertex, distance});

  while (!q.empty()) {
    count = q.size();
    distance++;

    while (count) {
      // Push all of q.front()'s children.
      for (int j = 0; j < numVertices; ++j) {
        if (adjacencyMatrix[q.front()][j] && visited.find(j) == visited.end()) {
          q.push(j);
          visited.insert({j, distance});
        }
      }

      q.pop();
      count--;
    }
  }

  return visited;
}

bool Graph::computeDistanceMatrix() {
  std::unordered_map<int, int> visited;

  for (int i = 0; i < numVertices; ++i) {
    visited = bfsWithDistance(i);
    for (auto it : visited) {
      distanceMatrix[i][it.first] = it.second;
    }
  }

  distanceMatrixComputed = true;
  // Return whether graph is connected or not.
  return (visited.size() == numVertices);
}

int Graph::shortestPath(int v1, int v2) {
  std::unordered_map<int, int> component = bfsWithDistance(v1);
  std::unordered_map<int, int>::const_iterator it = component.find(v2);

  return (it != component.end()) ? it->second : -1;
}

int Graph::getDiameter() {
  bool isConnected = computeDistanceMatrix();
  if (!isConnected) return -1;

  int diameter = 0;

  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < numVertices; ++j) {
      diameter = std::max(diameter, distanceMatrix[i][j]);
    }
  }

  return diameter;
}

void Graph::printComponents() {
  if (!distanceMatrixComputed) computeDistanceMatrix();

  std::vector<std::unordered_map<int, int>> connectedComponents;
  std::unordered_map<int, int> allVisited, component;

  // Gather connected components
  for (int i = 0; i < numVertices; ++i) {
    // Component with root i is its own component if we've never seen it before
    if (allVisited.find(i) == allVisited.end()) {
      component = bfsWithDistance(i);
      connectedComponents.push_back(component);
      allVisited.insert(component.begin(), component.end());
    }
  }

  // Print all connected components
  std::cout << "The graph has " << connectedComponents.size() << " connected components" << std::endl;

  for (int i = 0; i < connectedComponents.size(); ++i) {
    std::cout << "Connected component " << i + 1 << std::endl;

    for (auto it = connectedComponents[i].begin(); it != connectedComponents[i].end(); ++it) {
      std::cout << it->first << " -> ";
    }

    std::cout << std::endl;
  }
}

void Graph::printAdjacencyMatrix() {
  std::cout << "Adjacency matrix:" << '\n';
  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < numVertices; ++j) {
      std::cout << adjacencyMatrix[i][j] << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

void Graph::printDistanceMatrix() {
  std::cout << "Distance matrix:" << '\n';
  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < numVertices; ++j) {
      std::cout << distanceMatrix[i][j] << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}
