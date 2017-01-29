// Source: https://leetcode.com/problems/add-two-numbers/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:

    ListNode* addTwoNumbers(ListNode *a, ListNode *b) {
      if (!a && !b) return NULL;

      ListNode *preHead = new ListNode(0), *returnHead = preHead;
      int carry = 0, tmpSum = 0;

      while (a || b) {
        tmpSum = carry;
        if (a) tmpSum += a->val;
        if (b) tmpSum += b->val;
        returnHead->next = new ListNode(tmpSum % 10);
        carry = tmpSum / 10;

        if (a) a = a->next;
        if (b) b = b->next;
        returnHead = returnHead->next;
      }

      if (carry) {
        returnHead->next = new ListNode(carry);
      }

      returnHead = preHead->next;
      delete preHead;
      return returnHead;
    }
};
