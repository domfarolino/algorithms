class Solution {
private:
  struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
      return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
  };

  std::unordered_map<std::pair<int, int>, int, pair_hash> num_ways;

public:
  int numRollsToTarget(int d, int f, int target) {
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
      ways += numRollsToTarget(d - 1, f, target - rolls);
      ways %= int(std::pow(10, 9)) + 7;
    }

    num_ways.insert({std::make_pair(d, target), ways});
    return ways;
  }
};
