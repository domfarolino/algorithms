#include <iostream>
#include <vector>
#include <queue>

// Source: https://leetcode.com/contest/weekly-contest-86/problems/keys-and-rooms/

/**
 * Keys and Rooms
 * This problem is a basic BFS/DFS graph traversal where we want to
 * determine if the graph is connected or not. As stated, we can do this
 * either with BFS or DFS, I personally like BFS better so that's how I'll
 * be implementing. We should clarify that a room cannot have a key to itself
 * (aka, a self-destined edge), but even if it did, our BFS shouldn't have an
 * issue with it. We should clarify that there will at least be one room to start
 * in (room 0), though it need not have any keys to anything else. Should also verify
 * that rooms will only have keys to the rooms appearing in the list. The rest is basic
 * BFS implementation where want to:
 *
 * - Create a visited store/array, of size n (n = #rooms)
 * - Take an entry node, push it to the queue
 * - Mark it as visited
 * - Push unvisited neighbors to the queue
 * - Rinse and repeat while queue is not empty
 *
 * Once we're done with BFS from the entry node/room, we can see if every single
 * room has been visited or not. This is where we directly derive our return value!
 *
 * Complexity analysis
 * Time complexity: O(n), because only BFS from a single node/room
 * Space complexity: O(n)
 */

bool canVisitAllRooms(const std::vector<std::vector<int> >& rooms) {
  std::vector<bool> visited(rooms.size());
  std::queue<int> q;
  q.push(0);
  int front;

  while(!q.empty()) {
    front = q.front();
    visited[front] = true;
    for (int i = 0; i < rooms[front].size(); i++) {
      if (!visited[rooms[front][i]]) q.push(rooms[front][i]);
    }

    q.pop();
  }

  for (int i = 0; i < visited.size(); i++) {
    if (!visited[i]) return false;
  }

  return true;
}

int main() {
  std::vector<std::vector<int> > rooms = {{1, 3}, {3, 0, 1}, {2}, {0}};
  std::cout << canVisitAllRooms(rooms) << std::endl;
  return 0;
}
