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

int main() {
  std::string init = "AB", target = "BABA";
  std::cout << can_obtain(init, target) << std::endl;
  return 0;
}
