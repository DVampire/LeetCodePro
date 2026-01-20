#
# @lc app=leetcode id=2816 lang=cpp
#
# [2816] Double a Number Represented as a Linked List
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
    ListNode* doubleIt(ListNode* head) {
        // If the leading digit is 5 or greater, doubling will create a new most-significant digit.
        // Prepend a node with value 0 to handle this carry seamlessly in the loop.
        if (head->val >= 5) {
            head = new ListNode(0, head);
        }

        ListNode* curr = head;
        while (curr != nullptr) {
            // The new value of the current digit is (val * 2) % 10.
            // We also add a carry of 1 if the NEXT digit is 5 or greater.
            int newVal = (curr->val * 2) % 10;
            
            if (curr->next != nullptr && curr->next->val >= 5) {
                newVal += 1;
            }
            
            curr->val = newVal;
            curr = curr->next;
        }

        return head;
    }
};
# @lc code=end