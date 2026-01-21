#
# @lc app=leetcode id=2816 lang=cpp
#
# [2816] Double a Number Represented as a Linked List
#
# @lc code=start
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
    int doubleHelper(ListNode* node) {
        if (node == nullptr) return 0;
        
        int carry = doubleHelper(node->next);
        int val = node->val * 2 + carry;
        node->val = val % 10;
        return val / 10;
    }
    
    ListNode* doubleIt(ListNode* head) {
        int carry = doubleHelper(head);
        if (carry > 0) {
            ListNode* newHead = new ListNode(carry);
            newHead->next = head;
            head = newHead;
        }
        return head;
    }
};
# @lc code=end