// Source: https://leetcode.com/problems/linked-list-cycle/
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
    bool hasCycle(ListNode *head) {
        if (!head) return false;

        ListNode *slow = head, *fast = head->next;

        while (slow != fast) {
            slow = slow->next;
            if (!fast || !fast->next) return false;
            fast = fast->next->next;
        }

        return true;
    }
};
