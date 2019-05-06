#include <string>
#include <iostream>
#include <algorithm>

// Source: https://arena.topcoder.com/#/u/practiceCode/16527/48825/13918/2/326683

std::string can_obtain(std::string& init, std::string& target) {
  while (target != init && target.size() > init.size()) {
    if (target[target.size() - 1] == 'A')
      target.pop_back();
    else {
      target.pop_back();
      std::reverse(target.begin(), target.end());
    }
  }

  return (target == init) ? "Possible" : "Impossible";
}

// This algorithm takes in a string |a|, whose substring described by the bounds
// [i, j] is compared with another string |b|. If the indices are reversed, this
// algorithm accounts for it. The spread covered by [i, j] is assumed to be the
// same size as |b.size()|, so that we won't run off the end of |b|.
bool is_equal(const std::string& a, int i, int j, bool r, const std::string& b) {
  // Assert: abs(j - i) + 1 == b.size().
  int n = 0;
  if (!r) { // not reversed
    while (i <= j)
      if (a[i++] != b[n++]) return false;
  } else { // indices are reversed.
    while (j <= i)
      if (a[i--] != b[n++]) return false;
  }

  return true;
}

std::string can_obtain_optimal(std::string& init, std::string& target) {
  int i = 0, j = target.size() - 1;
  bool reversed = false;
  while ((!reversed && j - i + 1 > init.size()) ||
         (reversed && i - j + 1 > init.size())) {
    if (target[j] == 'A') {
      j = (!reversed) ? j - 1 : j + 1;
    } else {
      j = (!reversed) ? j - 1 : j + 1;
      std::swap(i, j);
      reversed = (reversed) ? false : true;
    }
  }

  return is_equal(target, i, j, reversed, init) ? "Possible" : "Impossible";
}

int main() {
  std::string init = "AB", target = "BABA";
  std::cout << can_obtain(init, target) << std::endl;
  std::cout << can_obtain_optimal(init, target) << std::endl;
  return 0;
}
