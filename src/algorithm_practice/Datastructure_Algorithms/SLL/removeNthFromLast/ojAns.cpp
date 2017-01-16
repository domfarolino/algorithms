// Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
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
    ListNode* removeNthFromEnd(ListNode *head, int n) {
        if (!head) return NULL;

        ListNode *fakeHead = new ListNode(0);
        fakeHead->next = head;

        ListNode *first = head, *second = fakeHead;

        // Advance first ptr by n - 1 nodes
        while (n - 1 && first) {
            first = first->next;
            n--;
        }

        // In case n is invalid
        if (!first) return head;

        // Advance both pointers at the same
        // pace until first = tail of list
        cout << "Got here af" << endl;
        while (first->next) {
            first = first->next;
            second = second->next;
        }

        ListNode *tmp = second->next;
        second->next = second->next->next;
        delete tmp;

        tmp = fakeHead->next;
        delete fakeHead;
        return tmp;
    }
};
