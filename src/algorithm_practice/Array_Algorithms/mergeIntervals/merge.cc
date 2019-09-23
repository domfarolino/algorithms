#include <algorithm> // std::sort
#include <vector>

// Custom comparator for an "interval". Reduces comparing two intervals to
// comparing their first value.
static bool compare(const std::vector<int>& i, const std::vector<int>& j) {
  return i[0] < j[1];
}

std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
  std::vector<std::vector<int>> return_intervals;
  std::sort(intervals.begin(), intervals.end(), compare);
  int i = 0, start, max_end_for_curr_run;
  while (i < intervals.size()) {
    start = intervals[i][0];
    max_end_for_curr_run = intervals[i][1];

    i++;
    while (i < intervals.size() && intervals[i][0] <= max_end_for_curr_run) {
      max_end_for_curr_run = std::max(max_end_for_curr_run, intervals[i][1]);
      i++;
    }

    return_intervals.push_back({start, max_end_for_curr_run});
  }

  return return_intervals;
}

int main() {
  std::vector<std::vector<int>> intervals = {{1, 5}, {2, 8}, {6, 9}};
  auto merged_intervals = merge(intervals);
  for (const auto& interval : merged_intervals) {
    printf("[%d, %d], ", interval[0], interval[1]);
  }

  printf("\n");
  return 0;
}
