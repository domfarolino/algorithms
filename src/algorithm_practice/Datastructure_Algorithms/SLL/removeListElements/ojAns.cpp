// Source: https://leetcode.com/problems/remove-linked-list-elements/description/

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
    ListNode* removeElements(ListNode* head, int val) {
        if (!head) return NULL;
        if (head->val == val) {
            delete head;
            return removeElements(head->next, val);
        } else {
            head->next = removeElements(head->next, val);
            return head;
        }
    }
};
