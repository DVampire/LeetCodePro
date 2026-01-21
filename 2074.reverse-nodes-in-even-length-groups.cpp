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
        ListNode dummy(0, head);
        ListNode* prevGroupEnd = &dummy;
        
        int groupNum = 1;
        
        while (prevGroupEnd->next) {
            // Count actual nodes in this group
            int count = 0;
            ListNode* curr = prevGroupEnd->next;
            while (curr && count < groupNum) {
                count++;
                curr = curr->next;
            }
            
            if (count % 2 == 0) {
                // Reverse this group
                ListNode* groupStart = prevGroupEnd->next;
                ListNode* prev = curr; // Node after the group (or nullptr)
                ListNode* node = groupStart;
                
                for (int i = 0; i < count; i++) {
                    ListNode* next = node->next;
                    node->next = prev;
                    prev = node;
                    node = next;
                }
                
                prevGroupEnd->next = prev;
                prevGroupEnd = groupStart;
            } else {
                // No reversal, just move prevGroupEnd to the end of this group
                for (int i = 0; i < count; i++) {
                    prevGroupEnd = prevGroupEnd->next;
                }
            }
            
            groupNum++;
        }
        
        return dummy.next;
    }
};
# @lc code=end