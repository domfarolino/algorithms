#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>

// Source: https://leetcode.com/problems/max-points-on-a-line/description/
// Source: https://www.geeksforgeeks.org/count-maximum-points-on-same-line/

/**
 * Max Points on a Line
 *
 * The description of this algorithm and complexities
 * can be found in the README in this directory.
 */

struct Point {
  int x, y;
  Point(int inX, int inY): x(inX), y(inY) {}
};

int maxPoints(std::vector<Point>& points) {
  if (!points.size()) return 0;
  int finalMaxSlope = 0, currMaxSlope, freePoints;
  double tmpSlope;
  std::unordered_map<double, int> slopeMap;
    for (int i = 0; i < points.size() - 1; ++i) {
      slopeMap.clear();
      freePoints = 0;
      currMaxSlope = 0;
      for (int j = i + 1; j < points.size(); ++j) {
        // Points are the same
        if (points[i].x == points[j].x && points[i].y == points[j].y) {
          freePoints++;
          continue;
        }

        if (points[i].x == points[j].x) {
          // No x-change = infinite slope
          tmpSlope = INT_MAX;
        } else if (points[i].y == points[j].y) {
          // No y-change = 0 slope
          tmpSlope = 0;
        } else {
          tmpSlope = double((points[i].x - points[j].x)) / (points[i].y - points[j].y);
        }

        slopeMap[tmpSlope]++;
        if (slopeMap[tmpSlope] > currMaxSlope)
          currMaxSlope = slopeMap[tmpSlope];
      }

      finalMaxSlope = std::max(finalMaxSlope, currMaxSlope + freePoints);
    }

  return finalMaxSlope + 1;
}

int main() {
  std::vector<Point> points = {Point(0, 0), Point(0, 0), Point(1, 0), Point(0, 1), Point(1, 1)};

  std::cout << maxPoints(points) << std::endl;
  return 0;
}
