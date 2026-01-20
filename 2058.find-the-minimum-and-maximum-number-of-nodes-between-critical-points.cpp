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
        // Need at least 3 nodes to have a critical point (prev, curr, next)
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        ListNode* prev = head;
        ListNode* curr = head->next;
        int currentIndex = 1; // Index of curr (head is 0)
        
        int firstCriticalIndex = -1;
        int lastCriticalIndex = -1;
        int minDistance = INT_MAX;

        // Iterate until curr is the last node (curr->next is null)
        while (curr->next) {
            ListNode* next = curr->next;
            
            // Check for local maxima or local minima
            if ((curr->val > prev->val && curr->val > next->val) || 
                (curr->val < prev->val && curr->val < next->val)) {
                
                if (firstCriticalIndex == -1) {
                    firstCriticalIndex = currentIndex;
                } else {
                    minDistance = min(minDistance, currentIndex - lastCriticalIndex);
                }
                lastCriticalIndex = currentIndex;
            }

            prev = curr;
            curr = next;
            currentIndex++;
        }

        if (minDistance == INT_MAX) {
            return {-1, -1};
        }

        int maxDistance = lastCriticalIndex - firstCriticalIndex;
        return {minDistance, maxDistance};
    }
};
# @lc code=end