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
        if (!head || !head->next || !head->next->next) return {-1, -1};
        
        int firstIdx = -1;
        int prevIdx = -1;
        int minDist = 1000000; // Larger than max possible distance (10^5)
        int currIdx = 1;
        
        ListNode* prevNode = head;
        ListNode* currNode = head->next;
        
        while (currNode->next != nullptr) {
            bool isMax = (currNode->val > prevNode->val && currNode->val > currNode->next->val);
            bool isMin = (currNode->val < prevNode->val && currNode->val < currNode->next->val);
            
            if (isMax || isMin) {
                if (firstIdx == -1) {
                    firstIdx = currIdx;
                } else {
                    int dist = currIdx - prevIdx;
                    if (dist < minDist) minDist = dist;
                }
                prevIdx = currIdx;
            }
            
            prevNode = currNode;
            currNode = currNode->next;
            currIdx++;
        }
        
        if (minDist == 1000000) return {-1, -1};
        
        return {minDist, prevIdx - firstIdx};
    }
};
# @lc code=end