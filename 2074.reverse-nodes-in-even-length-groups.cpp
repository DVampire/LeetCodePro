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
        // The first group (size 1) is always odd, so it's never reversed.
        // We start with prevGroupEnd at the head and groupSize = 2.
        if (!head || !head->next) return head;

        ListNode* prevGroupEnd = head;
        int groupSize = 2;

        while (prevGroupEnd->next) {
            // Count the actual number of nodes available for the current group
            ListNode* node = prevGroupEnd->next;
            int actualSize = 0;
            while (node != nullptr && actualSize < groupSize) {
                node = node->next;
                actualSize++;
            }

            if (actualSize % 2 == 0) {
                // Reverse the segment of length actualSize
                ListNode* curr = prevGroupEnd->next;
                ListNode* prev = nullptr;
                for (int i = 0; i < actualSize; ++i) {
                    ListNode* nextNode = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = nextNode;
                }
                
                // Reconnect the reversed segment
                // tail is the node that was at the start of the group before reversal
                ListNode* tail = prevGroupEnd->next;
                prevGroupEnd->next = prev;
                tail->next = curr;
                
                // Move prevGroupEnd to the end of the group we just processed
                prevGroupEnd = tail;
            } else {
                // If odd, we don't reverse; just skip the nodes
                for (int i = 0; i < actualSize; ++i) {
                    prevGroupEnd = prevGroupEnd->next;
                }
            }
            
            // Increment the intended group size for the next iteration
            groupSize++;
        }

        return head;
    }
};
# @lc code=end