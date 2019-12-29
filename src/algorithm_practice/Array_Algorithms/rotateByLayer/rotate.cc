#include <iostream>
#include <vector>
#include <string>

// These helpers were provided by Hackerrank.
std::string ltrim(const std::string&);
std::string rtrim(const std::string&);
std::vector<std::string> split(const std::string&);

void matrix_rotate_layer(std::vector<std::vector<int>>& matrix,
                         int top_offset, int left_offset, int m, int n, int r) {
  int tmp;
  for (int rotation = 0; rotation < r; ++rotation) {
    tmp = matrix[left_offset][top_offset];
    // Shift all |c| members of the top row to the left.
    for (int c = 0; c < n - 1; ++c) {
      matrix[top_offset][left_offset + c] =
        matrix[top_offset][left_offset + c + 1];
    }

    // Shift all |r| members of the right column up.
    for (int r = 0; r < m - 1; ++r) {
      matrix[top_offset + r][left_offset + n - 1] =
        matrix[top_offset + r + 1][left_offset + n - 1];
    }

    // Shift all |c| members of the bottom row to the right.
    for (int c = n - 1; c > 0; --c) {
      matrix[top_offset + m - 1][left_offset + c] =
        matrix[top_offset + m - 1][left_offset + c - 1];
    }

    // Shift all |r| members of the left column down.
    for (int r = m - 1; r > 0; --r) {
      matrix[top_offset + r][left_offset] =
        matrix[top_offset + r - 1][left_offset];
    }

    // Reset the tmp member.
    matrix[top_offset + 1][left_offset] = tmp;
  } // for.
}

void matrix_rotation(std::vector<std::vector<int>>& matrix, int rotations) {
  if (!matrix.size() || !matrix[0].size())
    return;
  int left_offset = 0, top_offset = 0;
  int m = matrix.size(), n = matrix[0].size();
  // Assert: min(m, n) % 2 == 0.

  int num_layers = std::min(m, n) / 2;
  int effective_rotations, perimeter;
  for (int layer = 0; layer < num_layers; ++layer) {
    perimeter = 2*m + 2*(n - 2);
    // The effective number of rotations is different for each layer, so we must
    // re-compute it for each layer.
    effective_rotations = rotations % perimeter;

    matrix_rotate_layer(matrix, top_offset, left_offset, m, n, effective_rotations);

    // Adjust for next layer.
    left_offset++;
    top_offset++;
    m -= 2;
    n -= 2;
  }
}

void print_matrix(const std::vector<std::vector<int>>& matrix) {
  for (int r = 0; r < matrix.size(); ++r) {
    for (int c = 0; c < matrix[0].size(); ++c) {
      std::cout << matrix[r][c];
      if (c != matrix[0].size() - 1) std::cout << " ";
    }

    if (r != matrix.size() - 1) std::cout << std::endl;
  }
}

int main() {
  std::string mnr_temp;
  getline(std::cin, mnr_temp);

  std::vector<std::string> mnr = split(rtrim(mnr_temp));

  int m = stoi(mnr[0]);
  int n = stoi(mnr[1]);
  int r = stoi(mnr[2]);

  std::vector<std::vector<int>> matrix(m);

  for (int i = 0; i < m; i++) {
    matrix[i].resize(n);

    std::string matrix_row_temp_temp;
    getline(std::cin, matrix_row_temp_temp);

    std::vector<std::string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

    for (int j = 0; j < n; j++) {
      int matrix_row_item = stoi(matrix_row_temp[j]);
      matrix[i][j] = matrix_row_item;
    }
  }

  matrix_rotation(matrix, r);
  print_matrix(matrix);
  return 0;
}

std::string ltrim(const std::string& str) {
  std::string s(str);
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
  return s;
}

std::string rtrim(const std::string& str) {
  std::string s(str);
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(), s.end());        
  return s;
}

std::vector<std::string> split(const std::string &str) {
  std::vector<std::string> tokens;

  std::string::size_type start = 0;
  std::string::size_type end = 0;

  while ((end = str.find(" ", start)) != std::string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
