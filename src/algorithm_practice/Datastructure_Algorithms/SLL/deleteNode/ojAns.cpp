// Source: https://leetcode.com/problems/remove-linked-list-elements/
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
    ListNode* removeElements(ListNode *head, int val) {
      if (!head) return NULL;

      ListNode *curr = head, *tmpNode;

      while (curr->next) {
        if (curr->next->val == val) {
          tmpNode = curr->next;
          curr->next = curr->next->next;
          delete tmpNode;
        } else {
          curr = curr->next;
        }
      }

      if (head->val == val) {
        tmpNode = head;
        head = head->next;
        delete tmpNode;
      }

      return head;
    }
};
