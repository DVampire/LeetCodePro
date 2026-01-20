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
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // Use a hash set for O(1) lookups
        unordered_set<int> st(nums.begin(), nums.end());
        
        // Use a dummy node to handle head removal easily
        ListNode dummy(0, head);
        ListNode* curr = &dummy;
        
        while (curr->next != nullptr) {
            if (st.count(curr->next->val)) {
                // The next node's value is in nums, so skip it
                curr->next = curr->next->next;
            } else {
                // The next node's value is not in nums, move forward
                curr = curr->next;
            }
        }
        
        return dummy.next;
    }
};
# @lc code=end