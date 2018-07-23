#include <iostream>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-84/problems/flipping-an-image/

/**
 * Flipping an image.
 * This problem is relatively simple and can be seen as a warm-up.
 * It is presented without further comment.
 *
 * Complexity analysis:
 * Time complexity: O(n^2), where n = # rows in the input matrix
 * Space complexity: O(1) (we can just modify the given image/matrix in-place)
 */

// We'll just modify the incoming image and return it
std::vector<std::vector<int> > flipAndInvertImage(std::vector<std::vector<int> >& image) {
  int left, right, tmpRight;
  for (int r = 0; r < image.size(); ++r) {
    left = 0;
    right = image[r].size() - 1;

    // Reverse & invert the current row
    while (left < right) {
      tmpRight = image[r][right];
      image[r][right] = !image[r][left];
      image[r][left] = !tmpRight;
      left++; right--;
    }

    // If row has odd # of members, invert middle member
    if (image.size() % 2 == 1) image[r][right] = !image[r][right];

  }

  return image;
}

int main() {
  std::vector<std::vector<int> > image = {{1, 1, 0}, {1, 0, 0}, {0, 0, 1}};
  flipAndInvertImage(image);

  for (int r = 0; r < image.size(); ++r) {
    std::cout << "{";

    for (int c = 0; c < image[r].size(); ++c) {
      std::cout << image[r][c] << ", ";
    }

    std::cout << "}, ";
  }

  return 0;
}
