#
# @lc app=leetcode id=2 lang=python3
#
# [2] Add Two Numbers
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        curr = dummy
        carry = 0
        
        while l1 or l2 or carry:
            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0
            
            # Calculate sum and carry
            total = val1 + val2 + carry
            carry = total // 10
            new_val = total % 10
            
            # Add node to result list
            curr.next = ListNode(new_val)
            curr = curr.next
            
            # Move to next nodes
            if l1: l1 = l1.next
            if l2: l2 = l2.next
            
        return dummy.next
# @lc code=end