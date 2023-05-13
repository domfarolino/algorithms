// Source: https://leetcode.com/problems/palindrome-linked-list/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head) return false;
        
        ListNode* fast = head
        ListNode* slow = head;
        ListNode* prev = nullptr;

        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }

        prev = slow;
        slow = slow->next;
        prev->next = nullptr;

        while (slow) {
            fast = slow->next;
            slow->next = prev;
            prev = slow;
            slow = fast;
        }

        fast = head;
        slow = prev;

        while (slow) {
            if (fast->val != slow->val) return false;
            fast = fast->next;
            slow = slow->next;
        }
        return true;
    }
};
