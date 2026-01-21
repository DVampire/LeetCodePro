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
class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // Convert nums to a set for O(1) lookup
        unordered_set<int> toRemove(nums.begin(), nums.end());
        
        // Find the new head by skipping nodes to be removed
        while (head != nullptr && toRemove.count(head->val)) {
            head = head->next;
        }
        
        // If all nodes were removed
        if (head == nullptr) {
            return nullptr;
        }
        
        // Remove nodes in the middle/end of the list
        ListNode* prev = head;
        ListNode* curr = head->next;
        
        while (curr != nullptr) {
            if (toRemove.count(curr->val)) {
                // Skip this node
                prev->next = curr->next;
            } else {
                // Move prev forward
                prev = curr;
            }
            curr = curr->next;
        }
        
        return head;
    }
};
# @lc code=end