#include <iostream>
#include <vector>
#include <map>

// Source: https://leetcode.com/contest/weekly-contest-87/problems/hand-of-straights/

/**
 * Hand of Straights
 * Given a vector of integers and an integer `w`, determine whether
 * or not the vector can be grouped into groups of `w` consecutive integers.
 * Of course a nice early-out for this is if the vector does not contain a factor
 * of `w` total cards, it obviously cannot be grouped into groups of `w` cards. We
 * should clarify some things:
 *
 * - Will the vector only contain integers? Yes
 * - Will `w` ever be larger than the size of the vector?
 *   The answer here is no, but we should be able to articulate why that is helpful.
 *   When we're iterating trying to determine if there are `w` consecutive numbers that
 *   a group can consist of, we don't want to just naively iterate `w` times in our array
 *   and go off the end. There's a pretty good chance our logic actually wouldn't do this by
 *   default, but this assumption could just give us more safety.
 *
 * Now to determine whether or not we can group the cards into groups of `w` consecutive cards.
 * We obviously want to pick a card, and see whether we can find `w - 1` consecutive cards that
 * can accompany it. Given [2, 1, 5, 4, 3, 3], w = 2; it's simply enough to realize that the groups
 * would be [1, 2, 3] and [3, 4, 5]. Hopefully that prompts the thought process that it matters which
 * number we start with when trying to find its group's other members. Yes `2` appears in a group, but
 * if we started with `2`, the first number in the hand we're given, we might want to think our first
 * group would be [2, 3, 4], which works, but then leaves us with [1, 3, 5] which is far from consecutive.
 * It should be realized that of course the first group will start with the lowest number, so we'll probably
 * want to sort vector of cards. Once we sort and get [1, 2, 3, 3, 4, 5] it is more obvious. We start with `1`
 * of course, and then in the sorted array we just need to find `w - 1` consecutive numbers. If we can't do that,
 * it's time to abort and return false. If we can, the next group should start with the smallest number in the
 * remaining list of unused numbers.
 *
 * One solution that came to my mind was to group the numbers into "buckets". The implementation would be a map
 * such that map[i] = n, where i is a number that appears in the original vector, and n is the number of times it
 * appears. We could iterate through the map in sorted-key-order. We start with the smallest bucket, and if it's value
 * is not 0, then we look for the next `w - 1` buckets and ensure that their values are not 0. If they are not, we decrement
 * them, and then decrement the bucket we started from. While our starting bucket value is 0 (of course it might not be), we
 * increment our iterator and find the next-smallest bucket and continue. Another solution that might be a little simpler, though
 * perhaps less efficient (I need to confirm), is to sort the original array, and keep an index variable at the beginning (the first
 * value in the group we're looking to complete). We can keep another index variable that starts at the first member, and iterates
 * forwards until it hits `w - 1` consecutively increasing values. If we ever reach the end of the array, we'll abort and return. if
 * we don't, we just need to keep remembering to make the values that we've already "used", into some sentinel value that won't appear
 * in an input array, like -1. This adds some gymnastics to be done in our implementation but it's not difficult. Once we're done with
 * a single group, we need to increment the index variable that indicates the start forward to the next non-(-1) value, and repeat. We
 * can continue until we go through the entire array. The only place we'd ever return false is if we're looking for a non-starting member
 * of a group and we hit the end of the array.
 *
 * Complexity analysis (TODO(domfarolino): confirm this)
 * Time complexity of array solution: O(n)
 * Space complexity of both solutions: O(n) (unless we manipulate the original array (i.e., fill it with -1s)
 */

bool isStraightHand(const std::vector<int>& hand, int w) {
  if (hand.size() % w) return false;

  std::map<int, int> map;
  for (int i = 0; i < hand.size(); i++) {
    map[hand[i]]++;
  }

  std::map<int, int>::iterator it = map.begin();
  std::map<int, int>::iterator next;

  while (it != map.end()) {
    // If the lowest bucket is 0 (this could
    // happen if the lowest bucket now has no
    // more remaining values, or if the next
    // lowest bucket now has no remaining values
    // because it was a part of the consecutive
    // sequence starting at another previous bucket
    if (it->second == 0) {
      it++;
      continue;
    }

    // For next w - 1 consecutive buckets
    // If consecutive bucket DNE or == 0,
    // we know we can't group them properly.
    // Else decrement it and look for the next
    it->second--;
    for (int i = 1; i < w; i++) {
      next = map.find(it->first + i);
      if (next == map.end() || next->second == 0) {
        return false;
      } else if (next->second) {
        next->second--;
      }
    }
  }

  return true;
}

bool isStraightHand2(std::vector<int> hand, int w) {
  if (hand.size() % w) return false;
  std::sort(hand.begin(), hand.end());

  std::vector<int>::iterator curr = hand.begin(), next;
  int tmp;
  while (curr != hand.end()) {
    tmp = *curr;
    next = curr;
    *curr = -1;

    for (int i = 1; i < w; i++) {
      next = std::find(next, hand.end(), tmp + 1);
      if (next != hand.end()) {
        tmp = *next;
        *next = -1;
      } else {
        return false;
      }
    }

    while (curr != hand.end() && *curr == -1) curr++;
  }

  return true;
}

int main() {
  std::vector<int> hand = {1, 2, 3, 6, 2, 3, 4, 7, 8};
  int w = 3;
  std::cout << isStraightHand(hand, w) << std::endl;
  std::cout << isStraightHand2(hand, w) << std::endl;
  hand = {1, 2, 2, 3, 4, 5, 6, 7, 8};
  std::cout << isStraightHand(hand, w) << std::endl;
  std::cout << isStraightHand2(hand, w) << std::endl;
  return 0;
}
