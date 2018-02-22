#include <iostream>

// Source: https://www.hackerrank.com/challenges/sock-merchant

/**
 * Sock Merchant
 * This problem is basically the same as
 * finding the number of pairs of identical items
 * in a list. The max length for each list is 100 and
 * the max number of items in each list is 100. We can read
 * in the entire list, and create a "map", or simple integer
 * array to act as a map. We can increment each value in the array
 * to denote the number of times some item appears in the original list.
 * We then can go through the entire map, and we know we can sell list[i]/2
 * pairs of an item for all items in the list. list[i]/2 makes sense here because
 * if have list[i] = 2, we can only sell one pair, or list[i]/2. If list[i] = 3, we
 * still can only sell floor(3/2) = 1 pairs.
 */

int main() {
  int n, tmpItem;
  int list[101] = {0};
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmpItem;
    list[tmpItem]++;
  }

  int totalPairs = 0;
  for (int i = 1; i < 101; ++i) {
    totalPairs += list[i] / 2;
  }

  std::cout << totalPairs << std::endl;

  return 0;
}
