#
# @lc app=leetcode id=2807 lang=cpp
#
# [2807] Insert Greatest Common Divisors in Linked List
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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        auto gcd = [](int a, int b) -> int {
            while (b) {
                int t = b;
                b = a % b;
                a = t;
            }
            return a;
        };
        ListNode* cur = head;
        while (cur != nullptr && cur->next != nullptr) {
            int g = gcd(cur->val, cur->next->val);
            ListNode* nxt = cur->next;
            cur->next = new ListNode(g, nxt);
            cur = nxt;
        }
        return head;
    }
};
# @lc code=end