#include <iostream>
#include <vector>
#include <queue>

// Source: https://www.hackerrank.com/challenges/torque-and-development/

// Description of the solution can be found in README.md

int componentSize(int rootCity, const std::vector<std::vector<int> >& adjList, std::vector<bool>& visited) {
  int returnSize = 0;
  std::queue<int> q;
  q.push(rootCity);

  // Basic BFS. In this implementation we sloppily push anything
  // onto the queue and then later check to see if we should actually
  // process it. Another way we could go about it is only push things
  // to the queue that we've never seen before, and guarantee that when
  // we come across it in the queue, it is "unvisited". It just depends where
  // we want our visited-checking logic to go. This implementation will allow
  // our queue to grow unnecessarily large though, technically.
  while (!q.empty()) {
    if (visited[q.front()]) {
      q.pop();
      continue;
    }

    // This node is unique and we haven't visited it yet
    // We want to count it as a member of our connected component
    visited[q.front()] = true;
    returnSize++;

    // Push every neighbor of q.front() to the queue. Later once
    // we come across it, we'll only count it if we've never seen it
    for (int i = 0; i < adjList[q.front()].size(); i++) {
      q.push(adjList[q.front()][i]);
    }

    // Pop
    q.pop();
  }

  return returnSize;
}

long roadsAndLibraries(int numCities, int cLib, int cRoad, std::vector<std::vector<int> > roads) {
  long returnResult = 0;
  std::vector<std::vector<int> > adjList(numCities);
  std::vector<bool> visited(numCities, 0);

  // Fill out adjacency list
  for (int i = 0; i < roads.size(); i++) {
    adjList[roads[i][0]].push_back(roads[i][1]);
    adjList[roads[i][1]].push_back(roads[i][0]);
  }

  int compSize;
  for (int i = 0; i < numCities; i++) {
    compSize = componentSize(i, adjList, visited);
    if (compSize) {
      returnResult += std::min(compSize * cLib, cLib + ((compSize - 1) * cRoad));
    }
  }

  return returnResult;
}

int main() {
  int q;
  std::cin >> q;
  for (int i = 0; i < q; i++) {
    int n;
    int m;
    int cLib;
    int cRoad;

    std::cin >> n >> m >> cLib >> cRoad;
    std::vector<std::vector<int> > roads(m, std::vector<int>(2));

    for (int road = 0; road < m; road++) {
      // Input all of our edges (roads)
      std::cin >> roads[road][0];
      roads[road][0]--;
      std::cin >> roads[road][1];
      roads[road][1]--;
    }

    long result = roadsAndLibraries(n, cLib, cRoad, roads);
    std::cout << result << std::endl;
  }

  return 0;
}
