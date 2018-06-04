// Source: https://leetcode.com/problems/hand-of-straights/description/

class Solution {
public:
std::map<int, int> preprocess(const std::vector<int>& hand) {
  std::map<int, int> returnMap;
  for (int i = 0; i < hand.size(); i++) {
    returnMap[hand[i]]++;
  }

  return returnMap;
}

bool isNStraightHand(std::vector<int> hand, int w) {
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
};
