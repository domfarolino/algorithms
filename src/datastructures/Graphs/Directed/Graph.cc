#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Graph.h"

Graph::Graph(int size): size_(std::max(size, 0)),
                        adjacency_matrix_(size_, std::vector<bool>(size_, false)),
                        distance_matrix_(size_, std::vector<int>(size_, -1)),
                        distance_matrix_computed_(false) {}

void Graph::AddEdge(int i, int j) {
  // TODO(domfarolino): How do we want to handle self-loops (i.e., i == j)?
  if (i < 0 || j < 0 || i >= size_ || j >= size_) {
    std::cerr << "Node for edge is out-of-bounds" << std::endl;
    return;
  }

  adjacency_matrix_[i][j] = true; // Directed edge.
  distance_matrix_computed_ = false;
}

std::vector<int> Graph::DFS(int vertex) {
  std::vector<int> return_vec;
  std::unordered_set<int> visited;
  DFSHelper(vertex, return_vec, visited);

  return return_vec;
}

void Graph::DFSHelper(int vertex, std::vector<int> &vec,
                                  std::unordered_set<int> &visited) {
  vec.push_back(vertex);
  visited.insert(vertex);

  // Only recurse on unvisited nodes.
  for (int j = 0; j < size_; ++j) {
    if (adjacency_matrix_[vertex][j] && visited.find(j) == visited.end()) {
      DFSHelper(j, vec, visited);
    }
  }
}

std::vector<int> Graph::BFS(int vertex) {
  std::vector<int> return_vec;
  std::unordered_set<int> visited;
  std::queue<int> q;

  q.push(vertex);
  visited.insert(vertex);

  while (!q.empty()) {
    return_vec.push_back(q.front());

    // Push all of q.front()'s children.
    for (int j = 0; j < size_; ++j) {
      if (adjacency_matrix_[q.front()][j] && visited.find(j) == visited.end()) {
        q.push(j);
        visited.insert(j);
      }
    }

    q.pop();
  }

  return return_vec;
}

std::unordered_map<int, int> Graph::BFSWithDistance(int vertex) {
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
      for (int j = 0; j < size_; ++j) {
        if (adjacency_matrix_[q.front()][j] && visited.find(j) == visited.end()) {
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

std::vector<std::unordered_map<int, int>> Graph::ConnectedComponents() {
  if (!distance_matrix_computed_) ComputeDistanceMatrix();

  std::vector<std::unordered_map<int, int>> connected_components;
  // TODO(domfarolino): We don't need the map's value here. Use an
  // std::unordered_set instead.
  std::unordered_map<int, int> all_visited, component;

  // Gather connected components
  for (int i = 0; i < size_; ++i) {

    // Only consider nodes which do not already belong to a component.
    if (all_visited.find(i) == all_visited.end()) {
      component = BFSWithDistance(i);
      connected_components.push_back(component);
      all_visited.insert(component.begin(), component.end());
    }

  }

  return connected_components;
}

bool Graph::ComputeDistanceMatrix() {
  std::unordered_map<int, int> visited;

  for (int i = 0; i < size_; ++i) {
    visited = BFSWithDistance(i);
    for (auto it : visited) {
      distance_matrix_[i][it.first] = it.second;
    }
  }

  distance_matrix_computed_ = true;
  // Return whether graph is connected or not.
  return (visited.size() == size_);
}

int Graph::ShortestPath(int v1, int v2) {
  std::unordered_map<int, int> component = BFSWithDistance(v1);
  std::unordered_map<int, int>::const_iterator it = component.find(v2);

  return (it != component.end()) ? it->second : -1;
}

int Graph::Diameter() {
  bool isConnected = ComputeDistanceMatrix();
  if (!isConnected) return -1;

  int diameter = 0;

  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      diameter = std::max(diameter, distance_matrix_[i][j]);
    }
  }

  return diameter;
}

void Graph::PrintConnectedComponents() {
  // Get all connected components.
  std::vector<std::unordered_map<int, int>> connected_components = ConnectedComponents();

  // Print all connected components
  std::cout << "The graph has " << connected_components.size() << " connected components" << std::endl;

  for (int i = 0; i < connected_components.size(); ++i) {
    std::cout << "Connected component " << i + 1 << std::endl;

    for (auto it = connected_components[i].begin(); it != connected_components[i].end(); ++it) {
      std::cout << it->first << " -> ";
    }

    std::cout << std::endl;
  }
}

void Graph::PrintAdjacencyMatrix() {
  std::cout << "Adjacency matrix:" << '\n';
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      std::cout << adjacency_matrix_[i][j] << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

void Graph::PrintDistanceMatrix() {
  std::cout << "Distance matrix:" << '\n';
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      std::cout << distance_matrix_[i][j] << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}
