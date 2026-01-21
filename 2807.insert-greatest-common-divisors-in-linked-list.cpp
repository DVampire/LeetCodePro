#
# @lc app=leetcode id=2807 lang=cpp
#
# [2807] Insert Greatest Common Divisors in Linked List
#
#include <numeric>

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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* cur = head;
        while (cur && cur->next) {
            ListNode* nxt = cur->next;
            int g = std::gcd(cur->val, nxt->val);
            ListNode* mid = new ListNode(g);
            cur->next = mid;
            mid->next = nxt;
            cur = nxt;
        }
        return head;
    }
};
# @lc code=end
