#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility> // std::pair.
#include <queue>

int min_path_knight(int n, int a, int b) {
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
  std::queue<std::pair<int, int>> q;
  q.push(std::make_pair(0, 0));

  int count = q.size();
  int path_length = 0;
  std::pair<int, int> front;
  std::vector<std::pair<int, int>> moves;
  while (q.size()) {

    // Expand the next level of breadth out.
    while (count) {
      // Pull the front-most move.
      front = q.front();
      // Assert: !visited[front.first][front.second].
      if (visited[front.first][front.second]) {
        q.pop();
        count--;
        continue;
      }

      visited[front.first][front.second] = true;

      if (front.first == n - 1 && front.second == n - 1)
        return path_length;


      // Produce all 8 possible moves.
      moves = {std::make_pair(front.first + a, front.second + b),
               std::make_pair(front.first + a, front.second - b),
               std::make_pair(front.first - a, front.second + b),
               std::make_pair(front.first - a, front.second - b),

               std::make_pair(front.first + b, front.second + a),
               std::make_pair(front.first + b, front.second - a),
               std::make_pair(front.first - b, front.second + a),
               std::make_pair(front.first - b, front.second - a),
              };

      // Only push in-bound un-visited moves to the queue.
      for (auto move : moves) {
        if (move.first < 0 || move.second < 0 || move.first >= n || move.second >= n ||
            visited[move.first][move.second]) {
          continue;
        }

        q.push(move);
      } // for.

      q.pop();
      count--;
    } // while.

    count = q.size();
    path_length++;

  } // while.

  return -1;
}

// TODO(domfarolino): Make the 1/2 grid optimization.
std::vector<std::vector<int>> knightlOnAChessboard(int n) {
  std::vector<std::vector<int>> answers(n - 1, std::vector<int>(n - 1, 99));

  for (int a = 1; a < n; ++a) {
    for (int b = 1; b < n; ++b) {
      answers[a - 1][b - 1] = min_path_knight(n, a, b);
    }
  }

  return answers;
}

int main() {
  std::string path = "test.out";
  std::ofstream fout(path);

  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<std::vector<int>> result = knightlOnAChessboard(n);

  for (int i = 0; i < result.size(); i++) {
    for (int j = 0; j < result[i].size(); j++) {
      fout << result[i][j];

      if (j != result[i].size() - 1) {
        fout << " ";
      }
    }

    if (i != result.size() - 1) {
      fout << "\n";
    }
  }

  fout << "\n";
  fout.close();
  return 0;
}
