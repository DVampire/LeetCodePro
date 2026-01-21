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
        static const int MAXV = 100000;
        vector<char> present(MAXV + 1, 0);
        for (int x : nums) present[x] = 1;

        ListNode dummy(0, head);
        ListNode* prev = &dummy;

        while (prev->next) {
            if (present[prev->next->val]) {
                ListNode* del = prev->next;
                prev->next = del->next;
                // Optional: delete del;  // not required on LeetCode
            } else {
                prev = prev->next;
            }
        }

        return dummy.next;
    }
};
# @lc code=end
