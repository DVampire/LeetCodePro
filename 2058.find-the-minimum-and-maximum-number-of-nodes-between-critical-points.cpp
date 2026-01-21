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
        // We need at least 3 nodes for a critical point
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }
        
        int firstCritical = -1, lastCritical = -1, prevCritical = -1;
        int minDist = INT_MAX;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        int index = 1;
        
        while (curr->next != nullptr) {
            ListNode* next = curr->next;
            
            // Check if current node is a critical point (local maxima or minima)
            if ((curr->val > prev->val && curr->val > next->val) || 
                (curr->val < prev->val && curr->val < next->val)) {
                if (firstCritical == -1) {
                    firstCritical = index;
                } else {
                    minDist = min(minDist, index - prevCritical);
                }
                prevCritical = index;
                lastCritical = index;
            }
            
            prev = curr;
            curr = next;
            index++;
        }
        
        // If fewer than 2 critical points, return [-1, -1]
        if (firstCritical == lastCritical) {
            return {-1, -1};
        }
        
        int maxDist = lastCritical - firstCritical;
        
        return {minDist, maxDist};
    }
};
# @lc code=end