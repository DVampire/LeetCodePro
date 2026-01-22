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
    ListNode* doubleIt(ListNode* head) {
        int carry = doubleHelper(head);
        if (carry > 0) {
            ListNode* newHead = new ListNode(carry);
            newHead->next = head;
            return newHead;
        }
        return head;
    }

private:
    int doubleHelper(ListNode* node) {
        if (!node) return 0;
        int carry = doubleHelper(node->next);
        int total = node->val * 2 + carry;
        node->val = total % 10;
        return total / 10;
    }
};
# @lc code=end