#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "directed_graph.h"

directed_graph::directed_graph(int size):
                      size_(std::max(size, 0)),
                      adjacency_matrix_(size_, std::vector<bool>(size_, false)),
                      distance_matrix_(size_, std::vector<int>(size_, -1)),
                      distance_matrix_computed_(false) {}

void directed_graph::add_edge(int i, int j) {
  // TODO(domfarolino): How do we want to handle self-loops (i.e., i == j)?
  if (i < 0 || j < 0 || i >= size_ || j >= size_) {
    throw std::logic_error("Node for edge is out-of-bounds");
  }

  adjacency_matrix_[i][j] = true; // Directed edge.
  distance_matrix_computed_ = false;
}

std::vector<int> directed_graph::dfs(int vertex) {
  std::vector<int> return_vec;
  std::unordered_set<int> visited;
  dfs_helper(vertex, return_vec, visited);

  return return_vec;
}

void directed_graph::dfs_helper(int vertex, std::vector<int> &vec,
                                std::unordered_set<int> &visited) {
  vec.push_back(vertex);
  visited.insert(vertex);

  // Only recurse on unvisited nodes.
  for (int j = 0; j < size_; ++j) {
    if (adjacency_matrix_[vertex][j] && visited.find(j) == visited.end()) {
      dfs_helper(j, vec, visited);
    }
  }
}

std::vector<int> directed_graph::bfs(int vertex) {
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

std::unordered_map<int, int> directed_graph::bfs_with_distance(int vertex) {
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

std::vector<std::unordered_map<int, int>> directed_graph::connected_components() {
  if (!distance_matrix_computed_) compute_distance_matrix();

  std::vector<std::unordered_map<int, int>> connected_components;
  // TODO(domfarolino): We don't need the map's value here. Use an
  // std::unordered_set instead.
  std::unordered_map<int, int> all_visited, component;

  // Gather connected components
  for (int i = 0; i < size_; ++i) {

    // Only consider nodes which do not already belong to a component.
    if (all_visited.find(i) == all_visited.end()) {
      component = bfs_with_distance(i);
      connected_components.push_back(component);
      all_visited.insert(component.begin(), component.end());
    }

  }

  return connected_components;
}

bool directed_graph::compute_distance_matrix() {
  std::unordered_map<int, int> visited;

  for (int i = 0; i < size_; ++i) {
    visited = bfs_with_distance(i);
    for (auto it : visited) {
      distance_matrix_[i][it.first] = it.second;
    }
  }

  distance_matrix_computed_ = true;
  // Return whether graph is connected or not.
  return (visited.size() == size_);
}

int directed_graph::shortest_path(int v1, int v2) {
  std::unordered_map<int, int> component = bfs_with_distance(v1);
  std::unordered_map<int, int>::const_iterator it = component.find(v2);

  return (it != component.end()) ? it->second : -1;
}

int directed_graph::diameter() {
  bool isConnected = compute_distance_matrix();
  if (!isConnected) return -1;

  int diameter = 0;

  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      diameter = std::max(diameter, distance_matrix_[i][j]);
    }
  }

  return diameter;
}

void directed_graph::PrintConnectedComponents() {
  // Get all connected components.
  std::vector<std::unordered_map<int, int>> components = connected_components();

  // Print all connected components
  std::cout << "The graph has " << components.size() << " connected components" << std::endl;

  for (int i = 0; i < components.size(); ++i) {
    std::cout << "Connected component " << i + 1 << std::endl;

    for (auto it = components[i].begin(); it != components[i].end(); ++it) {
      std::cout << it->first << " -> ";
    }

    std::cout << std::endl;
  }
}
