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
        if (!head) return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* prevGroup = &dummy;
        ListNode* curr = head;
        int groupSize = 1;

        while (curr) {
            // Find actual count of nodes in this group
            int cnt = 0;
            ListNode* temp = curr;
            while (temp && cnt < groupSize) {
                temp = temp->next;
                cnt++;
            }
            // temp is the node right after this group

            if (cnt % 2 == 0) {
                // Reverse cnt nodes starting at curr
                ListNode* node = curr;
                ListNode* prev = nullptr;
                for (int i = 0; i < cnt; i++) {
                    ListNode* nxt = node->next;
                    node->next = prev;
                    prev = node;
                    node = nxt;
                }
                // prev = new head of reversed group, curr = old head (now tail)
                prevGroup->next = prev;
                curr->next = temp;

                // Move pointers for next iteration
                prevGroup = curr;
                curr = temp;
            } else {
                // No reversal; just advance pointers cnt steps
                for (int i = 0; i < cnt; i++) {
                    prevGroup = curr;
                    curr = curr->next;
                }
            }

            groupSize++;
        }

        return dummy.next;
    }
};
# @lc code=end
