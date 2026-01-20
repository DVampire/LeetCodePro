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
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        while (head) {
            ListNode* nxt = head->next;
            head->next = prev;
            prev = head;
            head = nxt;
        }
        return prev;
    }

public:
    ListNode* doubleIt(ListNode* head) {
        head = reverseList(head);

        int carry = 0;
        ListNode* cur = head;
        ListNode* last = nullptr;

        while (cur) {
            int v = cur->val * 2 + carry;
            cur->val = v % 10;
            carry = v / 10;
            last = cur;
            cur = cur->next;
        }

        if (carry) {
            last->next = new ListNode(carry);
        }

        return reverseList(head);
    }
};
# @lc code=end
