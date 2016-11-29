#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Edge {
  string v1, v2;
  int weight;

  bool operator <(const Edge &otherEdge) const {
    return this->weight < otherEdge.weight;
  }

  Edge(string inV1, string inV2, int inWeight): v1(inV1), v2(inV2), weight(inWeight) {}
  Edge() {}
};

class Graph {
private:
  vector<string> vertices;
  vector<Edge> edges;

  /**
   * These data structures exist so we
   * can form disjoint sets for Kruskal's
   * algorithm.
   */
  unordered_map<string, string> parentMap;
  unordered_map<string, int> depthMap;

  /**
   * Find method is designed to take in
   * some vertex, and find the root of the
   * disjoint set the vertex is in.
   */
  string findRoot(string vertex) {
    string returnRoot = vertex;

    // Keep climbing up ancestral chain until we find the root
    while (parentMap[returnRoot] != returnRoot) {
      returnRoot = parentMap[returnRoot];
    }

    return returnRoot;
  }

  /**
   * Union method is designed to merge
   * two disjoint sets. How we merge two
   * sets/trees/graphs will affect our perf
   * we so we want to make the more shallow
   * tree a child of the deeper tree.
   */
  void mergeTrees(string root1, string root2) {
    if (depthMap[root1] > depthMap[root2]) {
      parentMap[root2] = root1;
    } else if (depthMap[root1] < depthMap[root2]) {
      parentMap[root1] = root2;
    } else {
      parentMap[root1] = root2;
      depthMap[root2]++;
    }
  }

  void createDisjointSets() {
    for (int i = 0; i < vertices.size(); ++i) {
      parentMap[vertices[i]] = vertices[i];
      depthMap[vertices[i]] = 0;
    }
  }

  /**
   * Method utilized by Prim's algorithm. Returns
   * a list of all edges incident to some given vertex
   * by traversing through this->edges. Inside each edge
   * the adjacent vertex can be found
   * Time complexity: O(e)
   */
  vector<Edge> findAdjacencies(const string& vertex) {
    vector<Edge> returnAdjacencies;

    for (int i = 0; i < this->edges.size(); ++i) {
      if (this->edges[i].v1 == vertex || this->edges[i].v2 == vertex) {
        returnAdjacencies.push_back(this->edges[i]);
      }
    }

    return returnAdjacencies;
  }

public:
  Graph(vector<string>& inVertices, vector<Edge>& inEdges): vertices(inVertices), edges(inEdges) {}

  void sortEdges() {
    sort(this->edges.begin(), this->edges.end());
  }

  void printEdges() {
    for (int i = 0; i < this->edges.size(); ++i) {
      cout << this->edges[i].weight << " " << this->edges[i].v1 << " " << this->edges[i].v2 << endl;
    }
  }

  /**
   * Kruskal's algorithm to find the minimum
   * cost spanning tree of a graph utilizes a
   * sorting algorithm and disjoint sets to compute
   * the minimum cost spanning tree.
   * Time complexity: O(e*log(e))
   * Space complexity: O(v + e)
   */
  vector<Edge> kruskal() {
    vector<Edge> minimumCostSpanningTree;
    this->sortEdges();
    this->createDisjointSets();

    string root1, root2;
    for (int i = 0; i < edges.size(); ++i) {
      root1 = findRoot(edges[i].v1);
      root2 = findRoot(edges[i].v2);

      /**
       * If root1 and root2 are not in the same
       * set, join them. If they are we don't need
       * to push this edge to the minimum cost spanning
       * tree. Regardless we know that the edge linking
       * root1's root with root2's root we come across first
       * is the shortest, since we sorted mate!
       */
      if (root1 != root2) {
        minimumCostSpanningTree.push_back(edges[i]);
        mergeTrees(root1, root2);
      }
    }

    return minimumCostSpanningTree;
  }

  /**
   * This version of Kruskal's algorithm assumes
   * the edges presented to it are in sorted order
   */
  vector<Edge> kruskalNoSort() {
    vector<Edge> minimumCostSpanningTree;

    this->createDisjointSets();

    string root1, root2;
    for (int i = 0; i < edges.size(); ++i) {
      root1 = findRoot(edges[i].v1);
      root2 = findRoot(edges[i].v2);

      /**
       * If root1 and root2 are not in the same
       * set, join them. If they are we don't need
       * to push this edge to the minimum cost spanning
       * tree. Regardless we know that the edge linking
       * root1's root with root2's root we come across first
       * is the shortest, since we sorted mate!
       */
      if (root1 != root2) {
        minimumCostSpanningTree.push_back(edges[i]);
        mergeTrees(root1, root2);
      }
    }

    return minimumCostSpanningTree;
  }

  /**
   * Prim's algorithm for finding the minimum
   * cost spanning tree of a weighted graph. The
   * algorithm works by utilizing two datastructures
   * to keep track of a "key" and a "parent" associated
   * with each vertex. We initialize each vertex parent as
   * null and each key is "infinite"/INT_MAX. We put all vertices
   * in a queue. We set the first vertex's key = 0, and then find
   * the vertex in the queue with the smallest key. At first this
   * will be the first node in the queue, by design. We're interested
   * in this vertex's adjacencies. We want to set each adjacent vertex's
   * parent value equal to the node we started with and its "key" value equal to
   * the weight of the edge connecting them if and only if the weight of that edge
   * is less than the adjacent vertex's key value.
   */
  vector<Edge> prim() {
    unordered_map<string, int> keyMap;
    unordered_map<string, string> parentMap;

    vector<Edge> minimumCostSpanningTree;
    vector<string> vertexQueue = this->vertices; // artificial queue

    // Initialize map values for each vertex
    for (int i = 0; i < vertices.size(); ++i) {
      parentMap[vertices[i]] = vertices[i]; // init as "null"
      keyMap[vertices[i]] = INT_MAX;
    }

    // Set our first "min" vertex by its key value
    keyMap[vertexQueue[0]] = 0;

    vector<string>::iterator minVertexIterator;
    string minVertex;
    vector<Edge> adjacencies;

    while (vertexQueue.size() != 0) {
      minVertexIterator = min_element(vertexQueue.begin(), vertexQueue.end(), [&](string v1, string v2){return keyMap[v1] < keyMap[v2];});
      minVertex = *minVertexIterator;
      vertexQueue.erase(minVertexIterator);

      // If minVertex has had its parent set
      if (parentMap[minVertex] != minVertex) {
        // Store the edge between minVertex and its parent
        cout << minVertex << " -- " << parentMap[minVertex] << endl;
      }

      adjacencies = findAdjacencies(minVertex);

      /**
       * For each adjacent vertex, if the vertex's
       * key is less than the edge weight between it
       * and the minVertex we want to update its key
       * and parent such that the adjacent vertex in
       * question is associated with the minVertex.
       */
      for (int i = 0; i < adjacencies.size(); ++i) {
        if (adjacencies[i].v1 == minVertex) {
          //cout << minVertex << "adjacency: " << adjacencies[i].v2 << endl;

          if (find(vertexQueue.begin(), vertexQueue.end(), adjacencies[i].v2) != vertexQueue.end() && adjacencies[i].weight < keyMap[adjacencies[i].v2]) {
            parentMap[adjacencies[i].v2] = minVertex;
            keyMap[adjacencies[i].v2] = adjacencies[i].weight;
          }

        } else if (adjacencies[i].v2 == minVertex) {
          //cout << minVertex << "adjacency: " << adjacencies[i].v1 << endl;

          if (find(vertexQueue.begin(), vertexQueue.end(), adjacencies[i].v1) != vertexQueue.end() && adjacencies[i].weight < keyMap[adjacencies[i].v1]) {
            parentMap[adjacencies[i].v1] = minVertex;
            keyMap[adjacencies[i].v1] = adjacencies[i].weight;
          }

        }
      }
    }

    return minimumCostSpanningTree;
  }
};

int main() {
  int numVertices, numEdges;
  cin >> numVertices >> numEdges;
  vector<string> vertices(numVertices);
  vector<Edge> edges(numEdges);

  /**
   * Process the input of vertices
   */
  for (int i = 0; i < numVertices; ++i) {
    cin >> vertices[i];
  }

  /**
   * Process the input of edges
   */
  for (int i = 0; i < numEdges; ++i) {
    cin >> edges[i].v1 >> edges[i].v2 >> edges[i].weight;
  }

  /**
   * Talk to Graph class to run Kruskal
   */
  Graph G(vertices, edges);
  vector<Edge> minimumCostSpanningTree = G.kruskal();

  G.prim();
  cout << endl << endl;

  // Print minimum spanning tree
  for (int i = 0; i < minimumCostSpanningTree.size(); ++i) {
    cout << minimumCostSpanningTree[i].v1 << " -- " << minimumCostSpanningTree[i].v2 << " " << minimumCostSpanningTree[i].weight << endl;
  }

  return 0;
}
