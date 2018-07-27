#include <iostream>
#include <vector>
#include <utility> // for std::pair
#include <algorithm>
#include <unordered_map>

// Source: https://leetcode.com/contest/weekly-contest-82/problems/most-profit-assigning-work/

/**
 * Max Profit Assignment
 * Fun problem. I like this one because it lended itself nicely to three different
 * solutions quite intuitively. First, some clarifications to realize are that we can't
 * assume the difficulty vector comes sorted, though it may appear that way from the examples.
 * It's also good to clarify and be sure you know that the lowest difficulty you can receive is
 * `1`, which is the same as the lowest worker ability. Also all of the inputs are of type int
 * (or vector<int>s), and we can expect not to overflow when adding up the profits we'll return.
 * The problem essentially comes down to, for each worker, find all jobs whose difficulty the worker
 * can complete, and choose the one with the highest profit.
 *
 * The naive solution to the above problem can be done by simply iterating through all workers, and
 * for all workers, iterate through all difficulties finding ones that:
 * 1.) The worker can complete
 * 2.) Has the maximum profit out of the ones we can complete
 * This requires keeping some "maxProfitForDifficulty" counter variable off to the side which we'll
 * update as we iterate through the difficulty list, and reset for each worker. At the end of iterating
 * we'll add its value to our return value and continue. It is straightforward, but also pretty expensive
 * since we're iterating through all the difficulties, for each worker.
 * Complexity analysis:
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 *
 * My thoughts on a more optimized solution was that we could find the max difficulty that a worker could
 * complete relatively quick if we sorted the difficulty vector. To ensure the positions of difficulties and
 * their associated profits don't get out-of-sync, we can zip up the difficulties and profits into a vector of
 * std::pair<int, int>s, and std::sort()'int this array actually automatically sorts by the `.first` entry of each
 * pair. With this, we still need to iterate through all of the workers, and run a binary search on the difficulty
 * vector, searching for the ability of the current worker, or the next lowest difficulty (this being the max difficulty
 * a worker can complete). This alone is not fully optimized. It is true we can find the job with the max difficulty that
 * a given worker can complete in O(log(n)), where n = |difficulty|, but as of right now we'd still have to iterate through
 * all previous difficulty/profit pairs to see which has the maximum profit. My idea for optimization around that was that we
 * could create a map that we build as we iterate through the sorted difficulty/profit pairs once, that associates each `difficulty`
 * with the maximum of all the `profits` between the lowest difficulty and it. In other words, it would tell us for each dificulty,
 * the maximum profit that can be obtained by a worker whose ability is >= `difficulty`. We could build this map, and then perform
 * the searching discussed earlier. Then, whenever we get the max difficulty in O(log(n)), we just look it up in our map to find the
 * max profit that can be obtained by a worker that can complete that difficulty, and voila!
 * Complexity analysis:
 * Time complexity: O(nlog(n)) + O(mlog(n))
 * Space complexity: O(n) + O(k), k = # unique difficulties (for our map) = O(n)
 *
 * There is another typically faster solution that requires sorting both the difficulty/profit pairs, as well as the worker vector.
 * After sorting it essentially requires a single, coordinated pass over both vectors. Let's see if you can figure it out.
 */

int findIdxOfDifficultyOrNextSmallest(const std::vector<std::pair<int, int>> sortedDifficulty, int key) {
  int l = 0, r = sortedDifficulty.size() - 1, m;

  while (l <= r) {
    m = (l + r) / 2;
    if (sortedDifficulty[m].first > key) {
      r = m - 1;
    } else if (sortedDifficulty[m].first < key) {
      l = m + 1;
    } else {
      return m;
    }
  }

  return (r < 0) ? -1 : r;
}

int maxProfitAssignment(const std::vector<int>& difficulty, const std::vector<int>& profit, const std::vector<int>& worker) {
  int maxProfit = 0, currMax = 0;
  std::vector<std::pair<int, int> > sortedDifficulty(difficulty.size());
  std::unordered_map<int, int> maxProfitOfDifficulty;

  // Zip up difficulties and profits
  for (int i = 0; i < difficulty.size(); ++i) {
    sortedDifficulty[i] = std::make_pair(difficulty[i], profit[i]);
  }

  // Sort difficulties and associated profits by difficulty
  std::sort(sortedDifficulty.begin(), sortedDifficulty.end());

  // Build maxProfitOfDifficulty map
  for (int i = 0; i < sortedDifficulty.size(); ++i) {
    currMax = std::max(currMax, sortedDifficulty[i].second);
    maxProfitOfDifficulty[sortedDifficulty[i].first] = currMax;
  }

  int idxOfAssignedDifficulty;
  for (int i = 0; i < worker.size(); ++i) {
    idxOfAssignedDifficulty = findIdxOfDifficultyOrNextSmallest(sortedDifficulty, worker[i]);
    if (idxOfAssignedDifficulty == -1) continue;
    maxProfit += maxProfitOfDifficulty[sortedDifficulty[idxOfAssignedDifficulty].first];
  }

  return maxProfit;
}

int main() {
  std::vector<int> difficulty = {49, 49, 76, 88, 100};
  std::vector<int> profit = {5, 8, 75, 89, 94};
  std::vector<int> worker = {98, 72, 16, 27, 76};
  std::cout << maxProfitAssignment(difficulty, profit, worker) << std::endl;
  return 0;
}
