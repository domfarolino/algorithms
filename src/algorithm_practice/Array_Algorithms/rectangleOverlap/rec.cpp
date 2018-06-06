#include <iostream>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-85/problems/rectangle-overlap/

/**
 * This one is pretty trivial. A key assumption is that for
 * a given rectangle, x1 <= x2 and y1 <= y2. This means the smallest
 * a rectangle can ever be is area = 0, and that x1 and y1 will always
 * be the smallest x and y values of a rectangle. Basically the idea here,
 * at least for my solution, is to first compare the x ranges of the rectangles
 * and then the y ranges. If both ranges overlap, we know the rectangles overlap.
 * If _just_ one range overlaps, no big deal. To determine if a given linear range
 * (nice and simplified problem now) overlaps, my thoughts were that we could take
 * the range with the smallest starting value, and determine if the starting value
 * of the other range falls >= the start of the first range & < the end of that same
 * range. Since we know we already have a hold of the range with the smallest starting
 * value, we only have to compare the start value of the other range, and not even worry
 * about the end (since it'll only be larger than the start which doesn't tell us much).
 * One case I wasn't sure whether this worked for was when we're given two identical rectangles,
 * but working it out on paper makes it easy to see that we've got that covered.
 *
 * Complexity analysis
 * Time complexity: O(1)
 * Space complexity: O(1)
 */

bool rangesOverlap(int x1, int x2, int x3, int x4) {
  return (x1 <= x3) ? x3 < x2 : x1 < x4;
}

bool rectanglesOverlap(const std::vector<int>& rec1, const std::vector<int>& rec2) {
  bool xValuesOverlap = rangesOverlap(rec1[0], rec1[2], rec2[0], rec2[2]);
  bool yValuesOverlap = rangesOverlap(rec1[1], rec1[3], rec2[1], rec2[3]);

  return xValuesOverlap && yValuesOverlap;
}

int main() {
  int n, tmp;
  std::cin >> n;
  std::vector<int> r1(4), r2(4);

  for (int i = 0; i < n; i++) {
    std::cin >> r1[0];
    std::cin >> r1[1];
    std::cin >> r1[2];
    std::cin >> r1[3];
    std::cin >> r2[0];
    std::cin >> r2[1];
    std::cin >> r2[2];
    std::cin >> r2[3];
    std::cout << rectanglesOverlap(r1, r2) << std::endl;
  }

  return 0;
}
