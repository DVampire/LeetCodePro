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
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // If list has fewer than 3 nodes, no critical points can exist
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int firstCriticalIndex = -1;
        int prevCriticalIndex = -1;
        int lastCriticalIndex = -1;
        int minDistance = INT_MAX;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        int index = 1;

        while (curr->next != nullptr) {
            int prevVal = prev->val;
            int currVal = curr->val;
            int nextVal = curr->next->val;

            // Check if current node is a local maxima or minima
            if ((currVal > prevVal && currVal > nextVal) || (currVal < prevVal && currVal < nextVal)) {
                if (firstCriticalIndex == -1) {
                    firstCriticalIndex = index;
                } else {
                    // Update minimum distance between consecutive critical points
                    minDistance = min(minDistance, index - prevCriticalIndex);
                }
                lastCriticalIndex = index;
                prevCriticalIndex = index;
            }

            // Move to next node
            prev = curr;
            curr = curr->next;
            index++;
        }

        // If fewer than two critical points were found
        if (firstCriticalIndex == lastCriticalIndex) {
            return {-1, -1};
        }

        int maxDistance = lastCriticalIndex - firstCriticalIndex;
        return {minDistance, maxDistance};
    }
};
# @lc code=end