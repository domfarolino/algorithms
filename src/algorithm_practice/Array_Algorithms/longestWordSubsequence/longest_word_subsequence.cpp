#include <iostream>
#include <unordered_map>
#include <vector>

// Source: https://techdevguide.withgoogle.com/paths/foundational/find-longest-word-in-dictionary-that-subsequence-of-given-string

std::unordered_map<char, std::vector<int>> preprocess(const std::string& s) {
  std::unordered_map<char, std::vector<int>> index_map;
  for (int i = 0; i < s.size(); ++i)
    index_map[s[i]].push_back(i);

  return index_map;
}

// Directly from Searching_And_Sorting/binarySearchClosest/binarySearchClosest.cpp.
int searchOrLargest(const std::vector<int>& arr, int val) {
  int l = 0, r = arr.size() - 1, mid;

  while (l <= r) {
    mid = l + (r - l) / 2;
    if (arr[mid] > val) {
      r = mid - 1;
    } else if (arr[mid] < val) {
      l = mid + 1;
    } else if (arr[mid] == val) {
      return mid;
    }
  }

  return (l >= arr.size()) ? -1 : l;
}

bool is_subsequence(std::unordered_map<char, std::vector<int>>& u_map,
                    const std::string& word) {
  int last_matched_index = 0, matched_index;
  for (const char& c: word) {
    matched_index = searchOrLargest(u_map[c], last_matched_index);

    if (matched_index == -1)
      return false;
  }

  return true;
}

std::string longest_word_subsequence(const std::string& s,
                                     const std::vector<std::string>& word_list) {
  // We could sort |word_list| by descending length for a subtle improvement.
  std::unordered_map<char, std::vector<int>> u_map = preprocess(s);
  std::string longest_string_so_far;

  for (const std::string& word: word_list) {
    if (word.size() > longest_string_so_far.size() &&
        word.size() <= s.size() &&
        is_subsequence(u_map, word)) {
      longest_string_so_far = word;
    }
  }

  return longest_string_so_far;
}

int main() {
  std::string input_string, tmp;
  std::cin >> input_string;

  int num_words;
  std::vector<std::string> word_list;
  std::cin >> num_words;
  for (int i = 0; i < num_words; ++i) {
    std::cin >> tmp;
    word_list.push_back(tmp);
  }

  std::cout << longest_word_subsequence(input_string, word_list) << std::endl;
  return 0;
}
