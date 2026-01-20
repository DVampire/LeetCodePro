#include <numeric>

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
        if (!head || !head->next) {
            return head;
        }

        ListNode* curr = head;
        while (curr != nullptr && curr->next != nullptr) {
            int commonDivisor = std::gcd(curr->val, curr->next->val);
            
            // Create a new node with the GCD and point it to the next node
            ListNode* newNode = new ListNode(commonDivisor, curr->next);
            
            // Link current node to the new node
            curr->next = newNode;
            
            // Advance curr to the node after the newly inserted node
            curr = newNode->next;
        }

        return head;
    }
};
# @lc code=end