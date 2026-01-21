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
        vector<int> crit;
        ListNode* prev = nullptr;
        ListNode* cur = head;
        int pos = 1;
        while (cur && cur->next) {
            if (prev && cur->next &&
                ((cur->val > prev->val && cur->val > cur->next->val) ||
                 (cur->val < prev->val && cur->val < cur->next->val))) {
                crit.push_back(pos);
            }
            prev = cur;
            cur = cur->next;
            ++pos;
        }
        if (crit.size() < 2) {
            return {-1, -1};
        }
        int minDist = INT_MAX;
        for (size_t i = 1; i < crit.size(); ++i) {
            int dist = crit[i] - crit[i - 1];
            minDist = min(minDist, dist);
        }
        int maxDist = crit.back() - crit.front();
        return {minDist, maxDist};
    }
};
# @lc code=end