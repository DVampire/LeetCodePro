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
        if (!head || !head->next) return {-1, -1};
        int pos = 1;
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            if (curr->next && prev) {
                int v = curr->val;
                int p = prev->val;
                int n = curr->next->val;
                if ((v > p && v > n) || (v < p && v < n)) {
                    crit.push_back(pos);
                }
            }
            prev = curr;
            curr = curr->next;
            ++pos;
        }
        if (crit.size() < 2) return {-1, -1};
        int minD = INT_MAX;
        int maxD = crit.back() - crit.front();
        for (size_t i = 1; i < crit.size(); ++i) {
            minD = min(minD, crit[i] - crit[i - 1]);
        }
        return {minD, maxD};
    }
};
# @lc code=end