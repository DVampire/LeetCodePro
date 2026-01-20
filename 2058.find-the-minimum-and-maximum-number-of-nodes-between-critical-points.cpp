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
        // A critical point needs a previous and a next node, 
        // so the list must have at least 3 nodes.
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int firstIndex = -1;
        int prevIndex = -1;
        int minDist = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int currentIndex = 1;

        while (curr->next != nullptr) {
            ListNode* nextNode = curr->next;
            bool isMax = (curr->val > prev->val && curr->val > nextNode->val);
            bool isMin = (curr->val < prev->val && curr->val < nextNode->val);

            if (isMax || isMin) {
                if (firstIndex == -1) {
                    // First critical point found
                    firstIndex = currentIndex;
                } else {
                    // Calculate distance from the previous critical point
                    minDist = min(minDist, currentIndex - prevIndex);
                }
                // Update the last seen critical point index
                prevIndex = currentIndex;
            }

            // Move pointers forward
            prev = curr;
            curr = nextNode;
            currentIndex++;
        }

        // If minDist was never updated, we found fewer than 2 critical points
        if (minDist == INT_MAX) {
            return {-1, -1};
        }

        // Max distance is always between the first and the last critical point
        int maxDist = prevIndex - firstIndex;
        
        return {minDist, maxDist};
    }
};
# @lc code=end