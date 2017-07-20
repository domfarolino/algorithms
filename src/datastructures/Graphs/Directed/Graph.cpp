#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Graph.h"

#define MAX(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a >= _b ? _a : _b; })
#define MIN(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a <= _b ? _a : _b; })

Graph::Graph(int inNumVertices): numVertices(MAX(inNumVertices, 0)), distanceMatrixComputed(false) {
  this->initAdjacencyMatrix();
  this->initDistanceMatrix();
}

/**
 * Allocate memory for adjacency matrix
 */
void Graph::initAdjacencyMatrix() {
  this->adjacencyMatrix = new bool*[this->numVertices];

  for (int i = 0; i < this->numVertices; ++i) {
    this->adjacencyMatrix[i] = new bool[this->numVertices];
  }
}

/**
 * Allocate memory for distance matrix
 */
void Graph::initDistanceMatrix() {
  this->distanceMatrix = new int*[this->numVertices];

  for (int i = 0; i < this->numVertices; ++i) {
    this->distanceMatrix[i] = new int[this->numVertices];

    for (int j = 0; j < this->numVertices; ++j) {
      this->distanceMatrix[i][j] = -1;
    }
  }
}

/**
 * Since this graph implementation is undirected,
 * our adjacency matrix must remain symmetrical.
 */
void Graph::addEdge(int i, int j) {
  this->adjacencyMatrix[i][j] = true;
  this->adjacencyMatrix[j][i] = true;
  this->distanceMatrixComputed = false;
}

std::vector<int> Graph::dfs(int vertex) {
  std::vector<int> returnVec;
  std::unordered_set<int> visited;
  dfsHelper(vertex, returnVec, visited);

  return returnVec;
}

void Graph::dfsHelper(int vertex, std::vector<int> &vec, std::unordered_set<int> &visited) {
  if (visited.find(vertex) != visited.end()) return;

  vec.push_back(vertex);
  visited.insert(vertex);

  for (int j = 0; j < this->numVertices; ++j) {
    if (this->adjacencyMatrix[vertex][j]) {
      dfsHelper(j, vec, visited);
    }
  }
}

std::vector<int> Graph::bfs(int vertex) {
  std::vector<int> returnVec;
  std::unordered_set<int> visited;
  std::queue<int> q;

  q.push(vertex);

  while (!q.empty()) {
    if (visited.find(q.front()) != visited.end()) {
      q.pop();
      continue;
    }

    returnVec.push_back(q.front());

    // Push all of q.front()'s children
    for (int j = 0; j < this->numVertices; ++j) {
      if (this->adjacencyMatrix[q.front()][j]) {
        q.push(j);
      }
    }

    // Visit q.front()
    visited.insert(q.front());
    q.pop();
  }

  return returnVec;
}

std::unordered_map<int, int> Graph::bfsWithDistance(int vertex) {
  std::unordered_map<int, int> visited;
  std::queue<int> q;

  q.push(vertex);
  int count, distance = 0;

  while (!q.empty()) {
    if (visited.find(q.front()) != visited.end()) {
      q.pop();
      continue;
    }

    count = q.size();

    while (count) {
      // Push all of q.front()'s children
      for (int j = 0; j < this->numVertices; ++j) {
        if (this->adjacencyMatrix[q.front()][j]) {
          q.push(j);
        }
      }

      // Visit q.front()
      // This works nicely because insert will
      // not update an already existing value
      visited.insert({q.front(), distance});
      q.pop();
      count--;
    }

    distance++;
  }

  return visited;
}

bool Graph::computeDistanceMatrix() {
  std::unordered_map<int, int> visited;

  for (int i = 0; i < this->numVertices; ++i) {
    visited = bfsWithDistance(i);
    for (auto it : visited) {
      this->distanceMatrix[i][it.first] = it.second;
    }
  }

  this->distanceMatrixComputed = true;
  return (visited.size() == this->numVertices);
}

int Graph::shortestPath(int v1, int v2) {
  std::unordered_map<int, int> component = bfsWithDistance(v1);
  std::unordered_map<int, int>::const_iterator it = component.find(v2);

  return (it != component.end()) ? it->second : -1;
}

int Graph::getDiameter() {
  bool isConnected = this->computeDistanceMatrix();
  if (!isConnected) return -1;

  int diameter = 0;

  for (int i = 0; i < this->numVertices; ++i) {
    for (int j = 0; j < this->numVertices; ++j) {
      diameter = MAX(diameter, this->distanceMatrix[i][j]);
    }
  }

  return diameter;
}

void Graph::printComponents() {
  if (!this->distanceMatrixComputed) this->computeDistanceMatrix();

  std::vector<std::unordered_map<int, int> > connectedComponents;
  std::unordered_map<int, int> allVisited, component;

  // Gather connected components
  for (int i = 0; i < this->numVertices; ++i) {
    // Component with root i is its own component if we've never seen it before
    if (allVisited.find(i) == allVisited.end()) {
      component = bfsWithDistance(i);
      connectedComponents.push_back(component);
      allVisited.insert(component.begin(), component.end());
    }
  }

  // Print all connected components
  std::cout << "The graph has " << connectedComponents.size() << " connected components" << '\n';

  for (int i = 0; i < connectedComponents.size(); ++i) {
    std::cout << "Connected component " << i + 1 << '\n';

    for (auto it = connectedComponents[i].begin(); it != connectedComponents[i].end(); ++it) {
      std::cout << it->first << " -> ";
    }

    std::cout << '\n';
  }
}

void Graph::printAdjacencyMatrix() {
  std::cout << "Adjacency matrix:" << '\n';
  for (int i = 0; i < this->numVertices; ++i) {
    for (int j = 0; j < this->numVertices; ++j) {
      std::cout << this->adjacencyMatrix[i][j] << " ";
    }

    std::cout << '\n';
  }

  std::cout << '\n';
}

void Graph::printDistanceMatrix() {
  std::cout << "Distance matrix:" << '\n';
  for (int i = 0; i < this->numVertices; ++i) {
    for (int j = 0; j < this->numVertices; ++j) {
      std::cout << this->distanceMatrix[i][j] << " ";
    }

    std::cout << '\n';
  }

  std::cout << '\n';
}

Graph::~Graph() {
  for (int i = 0; i < this->numVertices; ++i) {
    delete[] this->adjacencyMatrix[i];
    delete[] this->distanceMatrix[i];
  }

  delete[] this->adjacencyMatrix;
  delete[] this->distanceMatrix;
}
