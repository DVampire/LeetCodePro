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
        // The first group always has length 1 (odd), so the head node stays the same.
        ListNode* prev = head;
        int groupLen = 2;

        while (prev->next) {
            ListNode* node = prev->next; // The first node of the current group
            int count = 0;
            ListNode* temp = node;
            
            // Count the actual number of nodes in this group
            while (count < groupLen && temp) {
                temp = temp->next;
                count++;
            }

            if (count % 2 == 0) {
                // Reverse the nodes in the current group
                ListNode* curr = node;
                ListNode* p = nullptr;
                for (int i = 0; i < count; ++i) {
                    ListNode* nextNode = curr->next;
                    curr->next = p;
                    p = curr;
                    curr = nextNode;
                }
                // After reversal:
                // p is the new head of the current group
                // node is the original head, now the tail of the group
                // curr is the head of the next group
                prev->next = p;
                node->next = curr;
                prev = node; // Move prev to the end of the current group
            } else {
                // If the count is odd, skip the nodes in the current group
                for (int i = 0; i < count; ++i) {
                    prev = prev->next;
                }
            }
            // Increment the expected size for the next group
            groupLen++;
        }

        return head;
    }
};
# @lc code=end