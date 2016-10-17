#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Source: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=660&page=show_problem&problem=5104

/**
 * 7092 - Islands in the Data Stream
 * Key with this one is just understanding
 * the different cases you run across. First
 * you only want to start looking for an island
 * that starts with a number greater than the one
 * previous to it. From there, we're only going to
 * come across a few kinds of numbers, but we're interested
 * in seeing all numbers before some number <= the value right
 * before our start point. For example given the integers:
 * 0 5 4 3 2 2 2 2 1 1 1 0
 * Our first starting point will obviously be 5, and we know we
 * care about all numbers after 5 that are greater than 0 since
 * we cannot include any number <= 0 in our island. Our goal is
 * to get the total number of islands starting at 5. So what do
 * we do when we come across a number > 0? Well obviously it can
 * be included in one island but what about others:
 * 0 5 4 6 3 0
 * The above array has 4 islands starting at 5. When we start at 5
 * we next evaluate 4. Since 4 < 5 we know 5 can form its own island
 * all by itself, so we can increment the number of islands but since
 * 4 is still >= 0, we can also include 4 in a larger island that includes
 * 5 & 4. We then come across 6. We can't do anything here but move on since
 * it is larger. Next we come across 3. Since 3 < min(currentIsland) but still
 * >= 0, we know our current island can stand alone so we again increment the
 * number of islands, and then include 3 in our larger island and hope there is
 * some later value that appears in between 3 and 0 so we can increment again.
 * Notice we need to know the minimum value in our current island at all times.
 * We also need to update it whenever we come across a value less than our current
 * minimum but big enough to still surpass the value right before our island's start.
 * As long as the minimum value is greater than the value before our island start, we
 * can keep moving forward, but right when we come across a value that is less than our
 * minimum and also less <= 0 (the value before our island start point) we know this value
 * could never be included in our island given our current start point. This means we increment
 * one final time, but then stop looking.
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 */

int numIslands(const vector<int>& row) {
  int returnIslands = 0, currentMin = INT_MAX;

  for (int i = 1; i < row.size(); ++i) {

    if (row[i] > row[i-1]) {
      currentMin = row[i];
      for (int j = i+1; j < row.size(); ++j) {
        if (row[j] <= row[i-1]) {
          returnIslands++;
          break;
        } else if (row[j] < currentMin && row[j] > row[i-1]) {
          currentMin = row[j];
          returnIslands++;
        }
      }
    }

  }

  return returnIslands;
}

int main() {
  int numTests;
  cin >> numTests;
  vector<int> row(12);

  for (int i = 0; i < numTests; ++i) {
    cin >> row[0]; // get rid of test number, it's just i+1 anyways
    for (int j = 0; j < 12; ++j) cin >> row[j];
    cout << i+1 << " " << numIslands(row) << endl;
  }

  return 0;
}
