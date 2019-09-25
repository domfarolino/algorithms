#include <iostream>
#include <unordered_map>
#include <utility> // std::pair

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator() (const std::pair<T1, T2>& pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

using DiceMap = std::unordered_map<std::pair<int, int>, int, pair_hash>;

int num_rolls(int d, int f, int target, DiceMap& num_ways) {
  if (num_ways.find(std::make_pair(d, target)) != num_ways.end()) {
    return num_ways[std::make_pair(d, target)];
  }

  if (!target || !d || target < d || target > d * f) {
    num_ways.insert({std::make_pair(d, target), 0});
    return 0;
  }

  if (d == 1 || d == target) {
    num_ways.insert({std::make_pair(d, target), 1});
    return 1;
  }

  int ways = 0;
  for (int rolls = 1; rolls <= std::min(f, target); ++rolls) {
    ways += num_rolls(d - 1, f, target - rolls, num_ways);
    ways %= int(std::pow(10, 9)) + 7;
  }

  num_ways.insert({std::make_pair(d, target), ways});
  return ways;
}

int main() {
  DiceMap dice_map;
  std::cout << num_rolls(3, 4, 5, dice_map) << std::endl;
  return 0;
}
