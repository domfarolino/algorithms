#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <string>

std::vector<std::string> split_string(std::string);

struct Location {
  int r, c;
  int decisions;
  Location(int i_r, int i_c, int i_decisions):
    r(i_r), c(i_c), decisions(i_decisions) {}
};

std::string countLuck(const std::vector<std::string>& matrix, int k) {
  // Assert: matrix.size() && matrix[0].size().

  int start_row = INT_MIN, start_col;
  int m = matrix.size(), n = matrix[0].size();

  // Find coordinates of "M".
  for (int r = 0; r < matrix.size(); ++r) {
    for (int c = 0; c < matrix[r].size(); ++c) {
      if (matrix[r][c] == 'M') {
        start_row = r;
        start_col = c;
      }
    }

    if (start_row != INT_MIN) break;
  } // for.

  // Assert: start_row != INT_MIN; i.e., we did find "M".
  std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

  Location start_location(start_row, start_col, 0);
  std::vector<Location> moves;
  std::queue<Location> q;
  q.push(start_location);
  Location front = q.front();
  std::pair<int, int> offsets[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  while (q.size()) {
    front = q.front();
    q.pop();

    if (visited[front.r][front.c] || front.decisions > k) {
      continue;
    }

    visited[front.r][front.c] = true;

    if (matrix[front.r][front.c] == '*') {
      if (front.decisions == k)
        return "Impressed";
      return "Oops!";
    }

    // Keep going.
    // Compute next possible moves.
    for (auto& offset: offsets) {
      int final_r = front.r + offset.first,
          final_c = front.c + offset.second;
      if (final_r >= 0 && final_c >= 0 && final_r < m && final_c < n &&
          matrix[final_r][final_c] != 'X' && !visited[final_r][final_c]) {
        moves.push_back(Location(final_r, final_c, front.decisions));
      } // if.

    } // for.

    // Update move decisions based on ambiguity.
    for (auto& move: moves) {
      // If a path decision (wand wave) must be made, that counts as a decision.
      if (moves.size() > 1)
        move.decisions++;
      q.push(move);
    } // for.

    moves.clear();
  } // while.

  return "Oops!";
}

int main() {
  int t;
  std::cin >> t;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (int t_itr = 0; t_itr < t; t_itr++) {
    std::string nm_temp;
    getline(std::cin, nm_temp);

    std::vector<std::string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);
    int m = stoi(nm[1]);

    std::vector<std::string> matrix(n);

    for (int i = 0; i < n; i++) {
      std::string matrix_item;
      getline(std::cin, matrix_item);

      matrix[i] = matrix_item;
    }

    int k;
    std::cin >> k;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string result = countLuck(matrix, k);

    std::cout << result << "\n";
  }

  return 0;
}

std::vector<std::string> split_string(std::string input_string) {
  std::string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
    return x == y and x == ' ';
  });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  std::vector<std::string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != std::string::npos) {
    splits.push_back(input_string.substr(i, pos - i));

    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(input_string.substr(i, std::min(pos, input_string.length()) - i + 1));
  return splits;
}
