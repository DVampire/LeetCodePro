#
# @lc app=leetcode id=2074 lang=cpp
#
# [2074] Reverse Nodes in Even Length Groups
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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev = dummy;
        int k = 1;
        while (true) {
            ListNode* group_start = prev->next;
            if (!group_start) break;
            ListNode* cur = group_start;
            int len = 0;
            ListNode* group_tail = nullptr;
            while (cur != nullptr && len < k) {
                group_tail = cur;
                cur = cur->next;
                ++len;
            }
            ListNode* next_group_start = cur;
            if (len % 2 == 0) {
                ListNode* old_start = group_start;
                ListNode* new_head = nullptr;
                cur = group_start;
                while (cur != next_group_start) {
                    ListNode* nxt = cur->next;
                    cur->next = new_head;
                    new_head = cur;
                    cur = nxt;
                }
                prev->next = new_head;
                old_start->next = next_group_start;
                prev = old_start;
            } else {
                prev = group_tail;
            }
            ++k;
        }
        return dummy->next;
    }
};
# @lc code=end
