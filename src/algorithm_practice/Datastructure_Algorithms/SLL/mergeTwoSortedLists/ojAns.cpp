// Source: https://leetcode.com/problems/merge-two-sorted-lists/description/

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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *curr1 = l1, *curr2 = l2, *tmp, *potentialNext;
        if (!l1 && !l2) return NULL;
        if (!l1 || !l2) return (l1) ? l1 : l2;

        while (curr1 && curr2) {
            if (curr1->val <= curr2->val) {
                potentialNext = curr1->next;
                if (potentialNext && potentialNext->val <= curr2->val) {
                    curr1 = curr1->next;
                } else {
                    tmp = curr1->next;
                    curr1->next = curr2;
                    curr1 = tmp;
                }
            } else {
                potentialNext = curr2->next;
                if (potentialNext && potentialNext->val < curr1->val) {
                    curr2 = curr2->next;
                } else {
                    tmp = curr2->next;
                    curr2->next = curr1;
                    curr2 = tmp;
                }
            }
        }

        return (l1->val <= l2->val) ? l1 : l2;
    }
};
