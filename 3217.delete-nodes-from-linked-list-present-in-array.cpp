#
# @lc app=leetcode id=3217 lang=cpp
#
# [3217] Delete Nodes From Linked List Present in Array
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
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // Convert vector to unordered_set for O(1) lookups
        unordered_set<int> numSet(nums.begin(), nums.end());
        
        // Create a dummy node to simplify head deletion logic
        ListNode dummy(0);
        dummy.next = head;
        ListNode* curr = &dummy;
        
        // Traverse the list
        while (curr->next != nullptr) {
            if (numSet.count(curr->next->val)) {
                // If the next node's value is in nums, skip it
                ListNode* temp = curr->next;
                curr->next = curr->next->next;
                // In a real environment, you might delete temp here: delete temp;
            } else {
                // Otherwise, move current pointer forward
                curr = curr->next;
            }
        }
        
        return dummy.next;
    }
};
# @lc code=end