// Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
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
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return NULL;
        ListNode *curr = head, *next = head->next;

        while (next) {
            if (curr->val == next->val) {
                next = next->next;
                delete curr->next;
                curr->next = next;
            } else {
                curr = next;
                next = next->next;
            }
        }

        return head;
    }
};
