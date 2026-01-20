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
        // The first group always has length 1, which is odd, so it's never reversed.
        // We start processing groups from the second group onwards.
        ListNode* prev = head;
        int expected_group_size = 2;

        while (prev->next) {
            // Step 1: Count the actual number of nodes in the current group.
            int actual_count = 0;
            ListNode* curr = prev->next;
            while (actual_count < expected_group_size && curr) {
                curr = curr->next;
                actual_count++;
            }

            // Step 2: Check if the actual count of nodes in this group is even.
            if (actual_count % 2 == 0) {
                // Reverse the nodes in the current group.
                ListNode* node = prev->next;
                ListNode* rev_prev = nullptr;
                for (int i = 0; i < actual_count; ++i) {
                    ListNode* next_temp = node->next;
                    node->next = rev_prev;
                    rev_prev = node;
                    node = next_temp;
                }

                // Step 3: Link the reversed group back into the original list.
                ListNode* tail = prev->next; // The original start node is now the tail.
                tail->next = node;           // Connect tail to the first node of the next group.
                prev->next = rev_prev;       // Connect prev to the new head of this group.
                prev = tail;                 // Move prev to the end of the current group.
            } else {
                // Step 4: If the count is odd, just skip the group.
                for (int i = 0; i < actual_count; ++i) {
                    prev = prev->next;
                }
            }

            // Step 5: Increase the expected size for the next sequential group.
            expected_group_size++;
        }

        return head;
    }
};
# @lc code=end