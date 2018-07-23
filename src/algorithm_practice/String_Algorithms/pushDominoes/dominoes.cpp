#include <iostream>
#include <vector>

// Source: https://leetcode.com/contest/weekly-contest-85/problems/push-dominoes/

/**
 * Push Dominoes
 * This is a cool problem. The "For the purposes of this question" part
 * of the problem description basically means if after a one second, a domino
 * has pressure from the right side, and after two seconds, it has 2 dominoes applying
 * pressure to it from the opposing (left) side, it will not be "overpowered" to the
 * side that has more dominoes falling. Instead it will fall to the direction that it
 * fell to first, which in this case is left (due to dominoes applying pressure from right).
 *
 * The problem may seem rather difficult at first, but realizing the problem is basically the
 * same as trying to figure out, for each domino, which side has pressure applied to it first
 * (because that is the way it will end up falling) is key. "Pressure" in this case is basically
 * direction over a period of time. If equal pressure is applied to a domino from both sides (both
 * left- and right-falling surrounding dominoes get to the domino in question at the same time) it
 * will not move. It is important to realize that "time" is just a way to explain the problem, however
 * an effective solution need not iterate through sequential seconds simulating the fall. We can instead
 * equate time and distance. Two seconds = two dominoes worth of distance.
 *
 * A naive approach to the problem would be for each domino in the list, iterate out from both sides and see
 * if you:
 *   - Hit an R from the left side before an L from the right side (in which case the domino would fall right).
 *   - Hit an L from the right side before an R from the left side (in which case the domino would fall left).
 *   - Hit an L and R from the right and left respectively at the same time (same distance away) (in which case domino would not move).
 * This would be fairly easy to implement, but is also relatively inefficient. Consider the below complexities.
 * Complexity analysis:
 * Time complexity: O(n^2) (n-1 iterations outward from each n domino)
 * Space complexity: O(1)
 *
 * The idea I had for an optimized solution was a two-pass solution. The idea is that want to keep track of how far
 * each domino is away from a right-falling domino towards its left. In other words, we'd keep track of how long it'd
 * take for a right-falling domino do the left of any given domino to affect it and push it right. Then with this, we'd
 * do another pass from the left, and for each domino that could be affected by a left-falling domino to its right, we'd
 * look at our distance "map" and see how far that same domino was from a right-falling domino. From this, we'd be able to
 * for each domino on this second pass, whether a left-falling domino would get to it first, a right falling domino would get
 * to it first, or if it was completely even (or also untouched). From this we'd be able to mutate a copy of the original string
 * and return it as the problem description asks.
 *
 * The implementation of our "distance map" that would keep track of how far any given domino was away from a right-falling domino
 * could simply be an array of length |n|, where |n| is the length of the input string, and |map[i]| is the distance that domino arr[i]
 * is away from a right-falling domino. This two-pass solution is not very difficult to implement and is much faster.
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

std::string pushDominoes(std::string str) {
  int distance;
  bool canApplyPressure = false;
  std::vector<int> rightDistMap(str.length());

  for (int i = 0; i < str.length(); i++) {
    if (str[i] == 'R') {
      distance = 0;
      canApplyPressure = true;
    } else if (str[i] == 'L') {
      canApplyPressure = false;
    } else {
      if (canApplyPressure)
        rightDistMap[i] = ++distance;
    }
  }

  canApplyPressure = false;
  for (int i = str.length() - 1; i >= 0; i--) {
    if (str[i] == 'L') {
      distance = 0;
      canApplyPressure = true;
    } else if (str[i] == 'R') {
      canApplyPressure = false;
    } else {
      if (canApplyPressure) {
        distance++;
        if (!rightDistMap[i] || rightDistMap[i] > distance)
          str[i] = 'L';
        else if (rightDistMap[i] < distance)
          str[i] = 'R';
      } else {
        if (rightDistMap[i]) str[i] = 'R';
      }
    }
  }

  return str;
}

int main() {
  int n;
  std::string input;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> input;
    std::cout << pushDominoes(input) << std::endl;
  }

  return 0;
}
