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
            int v1 = curr->val;
            int v2 = curr->next->val;
            
            // Calculate GCD using std::gcd (available in <numeric> since C++17)
            int commonDivisor = std::gcd(v1, v2);
            
            // Create the new node
            ListNode* newNode = new ListNode(commonDivisor);
            
            // Insert newNode between curr and curr->next
            newNode->next = curr->next;
            curr->next = newNode;
            
            // Skip the newly inserted node and move to the next original node
            curr = newNode->next;
        }

        return head;
    }
};
# @lc code=end