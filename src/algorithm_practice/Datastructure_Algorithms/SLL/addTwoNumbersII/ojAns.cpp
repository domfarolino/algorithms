// Source: https://leetcode.com/problems/add-two-numbers-ii/
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

    int lengthOfList(ListNode *head) {
      int returnLength = 0;

      while (head) {
        returnLength++;
        head = head->next;
      }

      return returnLength;
    }

    ListNode* addTwoNumbersHelper(ListNode *a, ListNode *b, int aLen, int bLen, int& carry) {
      if (!a && !b) return NULL;

      if (aLen != bLen) {
        ListNode *next = addTwoNumbersHelper(a->next, b, aLen - 1, bLen, carry);
        ListNode *returnHead = new ListNode((a->val + carry) % 10);
        returnHead->next = next;
        carry = (a->val + carry) / 10;
        return returnHead;
      }

      ListNode *next = addTwoNumbersHelper(a->next, b->next, aLen - 1, bLen - 1, carry);
      ListNode *returnHead = new ListNode((a->val + b->val + carry) % 10);
      returnHead->next = next;
      carry = (a->val + b->val + carry) / 10;
      return returnHead;
    }

    ListNode* addTwoNumbers(ListNode *a, ListNode *b) {
      int aLen = lengthOfList(a), bLen = lengthOfList(b), carry = 0;
      ListNode *returnHead;
      if (aLen >= bLen) returnHead = addTwoNumbersHelper(a, b, aLen, bLen, carry);
      else returnHead = addTwoNumbersHelper(b, a, bLen, aLen, carry);

      if (carry) {
        ListNode *preHead = new ListNode(carry);
        preHead->next = returnHead;
        return preHead;
      }

      return returnHead;
    }


};
