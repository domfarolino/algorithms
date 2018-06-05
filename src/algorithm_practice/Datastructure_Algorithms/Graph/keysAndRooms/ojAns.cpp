// Source: https://leetcode.com/contest/weekly-contest-86/problems/keys-and-rooms/

class Solution {
public:
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
};
