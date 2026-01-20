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
        unordered_set<int> s;
        s.reserve(nums.size() * 2);
        for (int x : nums) s.insert(x);

        ListNode dummy(0, head);
        ListNode* cur = &dummy;

        while (cur->next) {
            if (s.count(cur->next->val)) {
                cur->next = cur->next->next; // delete by bypassing
            } else {
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};
# @lc code=end
