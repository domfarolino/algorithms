class Solution {
public:
  int search(const std::vector<int>& vec, int val) {
    int l = 0, r = int(vec.size()) - 1, mid;
    while (l <= r) {
      mid = l + (r - l) / 2;
      if (vec[mid] < val)
        l = mid + 1;
      else if (vec[mid] > val)
        r = mid - 1;
      else if (vec[mid] == val)
        return mid;
    }

    return l;
  }

  string smallestSubsequence(const string& text) {
    std::string return_string;
    std::map<char, std::vector<int>> indices;
    int idx = -1;

    // Build |indices|.
    for (int i = 0; i < text.size(); ++i)
      indices[text[i]].push_back(i);

    std::set<int> max_indices;
    for (const auto& entry: indices)
      max_indices.insert(entry.second[entry.second.size() - 1]);

    int next_idx, smallest_max;
    while (indices.size() > 1) {
      smallest_max = *max_indices.begin();
      for (const auto& entry: indices) {
        // See if this letter's next index > idx
        // is also < |smallest_max|.
        next_idx = search(entry.second, idx);
        if (entry.second[next_idx] > smallest_max) continue;

        // Assert |next_idx| < smallest_max.
        idx = entry.second[next_idx];
        max_indices.erase(entry.second[entry.second.size() - 1]);
        return_string.push_back(entry.first);
        indices.erase(entry.first);
        break;
      }
    }

    return_string.push_back(indices.begin()->first);
    return return_string;
  }
};
