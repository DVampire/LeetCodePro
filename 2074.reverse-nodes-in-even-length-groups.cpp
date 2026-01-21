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
        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy;
        ListNode* node = head;
        int group_size = 1;
        while (node != nullptr) {
            ListNode* group_start = node;
            ListNode* group_end = group_start;
            int actual_len = 1;
            for (int i = 1; i < group_size; ++i) {
                if (group_end->next == nullptr) break;
                group_end = group_end->next;
                ++actual_len;
            }
            ListNode* next_group = group_end->next;
            if (actual_len % 2 == 0) {
                // Reverse the group
                ListNode* prev_rev = nullptr;
                ListNode* curr_rev = group_start;
                while (curr_rev != next_group) {
                    ListNode* temp = curr_rev->next;
                    curr_rev->next = prev_rev;
                    prev_rev = curr_rev;
                    curr_rev = temp;
                }
                // Connect prev to new start (old end)
                prev->next = prev_rev;
                // Connect old start (new end) to next group
                group_start->next = next_group;
                // Update prev to new end of group
                prev = group_start;
            } else {
                // No reversal, update prev to group_end
                prev = group_end;
            }
            node = next_group;
            ++group_size;
        }
        return dummy->next;
    }
};
# @lc code=end