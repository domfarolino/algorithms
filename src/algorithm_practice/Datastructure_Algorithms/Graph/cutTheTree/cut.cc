#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

// Hackerrank-provided.
std::string ltrim(const std::string&);
std::string rtrim(const std::string&);
std::vector<std::string> split(const std::string&);

/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

int sum_tree(int root, std::vector<std::pair<int, std::vector<int>>>& tree, std::unordered_set<int>& visited) {
  if (visited.find(root) != visited.end()) {
    return 0;
  }

  visited.insert(root);
  int sum = tree[root].first;
  for (const int& child: tree[root].second) {
    sum += sum_tree(child, tree, visited);
  }

  tree[root].first = sum;
  return sum;
}

void get_min_diff(int root,
              const std::vector<std::pair<int, std::vector<int>>>& tree,
              int& min_diff,
              std::unordered_set<int>& visited) {
  if (visited.find(root) != visited.end())
    return;

  visited.insert(root);

  int tree_sum = tree[0].first;
  int subtree_sum = tree[root].first;
  int rest_of_tree_sum = tree_sum - subtree_sum;
  // Assert: |rest_of_tree_sum| > 0.
  for (const int& child: tree[root].second) {
    get_min_diff(child, tree, min_diff, visited);
    min_diff = std::min(min_diff, std::abs(rest_of_tree_sum - subtree_sum));
  }
}

int cutTheTree(std::vector<int> data, std::vector<std::pair<int, int>> edges) {
  std::vector<std::pair<int, std::vector<int>>> tree(data.size());
  for (int i = 0; i < data.size(); ++i)
    tree[i].first = data[i];

  for (const std::pair<int, int>& edge: edges) {
    // Edges are bi-directional, but we use a visited set to prevent us from
    // creating a cycle.
    tree[edge.first].second.push_back(edge.second);
    tree[edge.second].second.push_back(edge.first);
  }

  // Sum the tree per-node (DFS).
  std::unordered_set<int> visited;
  sum_tree(0, tree, visited);

  int min_diff = INT_MAX;
  // Traverse the tree (DFS).
  visited.clear();
  get_min_diff(0, tree, min_diff, visited);

  return min_diff;
}

int main() {
    std::string n_temp;
    getline(std::cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    std::string data_temp_temp;
    getline(std::cin, data_temp_temp);

    std::vector<std::string> data_temp = split(rtrim(data_temp_temp));
    std::vector<int> data(n);

    for (int i = 0; i < n; i++) {
      int data_item = stoi(data_temp[i]);

      data[i] = data_item;
    }

    std::vector<std::pair<int, int>> edges(n - 1);

    for (int i = 0; i < n - 1; i++) {
      std::string edges_row_temp_temp;
      getline(std::cin, edges_row_temp_temp);

      std::vector<std::string> edges_row_temp = split(rtrim(edges_row_temp_temp));

      edges[i].first = stoi(edges_row_temp[0]) - 1;
      edges[i].second = stoi(edges_row_temp[1]) - 1;
    }

    int result = cutTheTree(data, edges);
    std::cout << result << "\n";
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
