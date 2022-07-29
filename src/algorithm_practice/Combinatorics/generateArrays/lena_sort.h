int lena_sort(std::vector<int> nums) {
  int comparisons = 0;

  if (nums.size() <= 1)
    return comparisons;

  int pivot = nums[0];
  std::vector<int> less, more;

  for (int i = 1; i < nums.size(); ++i) {
    // Comparison
    comparisons++;
    if (nums[i] < pivot) {
      less.push_back(nums[i]);
    } else {
      more.push_back(nums[i]);
    }
  }

  int left_comparisons = lena_sort(less),
      right_comparisons = lena_sort(more);
  return comparisons + left_comparisons + right_comparisons;
}
