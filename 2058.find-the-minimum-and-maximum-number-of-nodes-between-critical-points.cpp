#
# @lc app=leetcode id=2058 lang=cpp
#
# [2058] Find the Minimum and Maximum Number of Nodes Between Critical Points
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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }
        
        int firstCritical = -1;
        int prevCritical = -1;
        int minDistance = INT_MAX;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        int position = 1;
        
        while (curr->next) {
            ListNode* next = curr->next;
            
            // Check if current node is a critical point
            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {
                
                if (firstCritical == -1) {
                    firstCritical = position;
                } else {
                    minDistance = min(minDistance, position - prevCritical);
                }
                prevCritical = position;
            }
            
            prev = curr;
            curr = next;
            position++;
        }
        
        // If fewer than 2 critical points
        if (firstCritical == -1 || prevCritical == firstCritical) {
            return {-1, -1};
        }
        
        int maxDistance = prevCritical - firstCritical;
        
        return {minDistance, maxDistance};
    }
};
# @lc code=end