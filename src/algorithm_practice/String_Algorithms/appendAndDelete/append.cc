#include <iostream>
#include <vector>
#include <string>

// Complete the appendAndDelete function below.
std::string appendAndDelete(const std::string& s, const std::string& t, int k) {
  if (k >= s.size() + t.size())
    return "Yes";

  int substr_match_length = 0;
  int i = 0;
  while (i < s.size() && i < t.size()) {
    if (s[i] == t[i]) {
      substr_match_length++;
      i++;
    } else break;
  }

  int remaining_unmatched_s = s.size() - substr_match_length;
  int remaining_unmatched_t = t.size() - substr_match_length;
  int diff = remaining_unmatched_s + remaining_unmatched_t;
  if (k < diff)
    return "No";

  // Actually have to do work to find out.
  if ((k - diff) % 2 == 0)
    return "Yes";
  
  return "No";
}

int main() {
  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // std::cin >> n; // Test cases.

  std::string s, t;
  for (int i = 0; i < n; ++i) {
    getline(std::cin, s);
    getline(std::cin, t);

    int k;
    std::cin >> k;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string result = appendAndDelete(s, t, k);

    std::cout << result << "\n";
  }

  return 0;
}
