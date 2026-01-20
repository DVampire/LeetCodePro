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
        if (!head || !head->next) return head;

        ListNode* prev = head; // The tail of the previous group
        int groupLen = 2; // Next group length we are looking for

        while (prev->next) {
            ListNode* curr = prev->next;
            ListNode* probe = curr;
            int count = 0;
            
            // Count actual nodes available for the current group
            while (count < groupLen && probe) {
                probe = probe->next;
                count++;
            }

            if (count % 2 == 0) {
                // Reverse 'count' nodes starting from 'curr'
                ListNode* currGroupPrev = nullptr;
                ListNode* currGroupNode = curr;
                ListNode* currGroupNext = nullptr;
                
                for (int i = 0; i < count; i++) {
                    currGroupNext = currGroupNode->next;
                    currGroupNode->next = currGroupPrev;
                    currGroupPrev = currGroupNode;
                    currGroupNode = currGroupNext;
                }
                
                // Connect previous group to the new head of this reversed group
                prev->next = currGroupPrev;
                // Connect the new tail of this reversed group to the next group
                curr->next = currGroupNode;
                // Move prev to the new tail of this group
                prev = curr;
            } else {
                // Odd length, just advance prev to the end of this group
                for (int i = 0; i < count; i++) {
                    prev = prev->next;
                }
            }
            
            groupLen++;
        }

        return head;
    }
};
# @lc code=end