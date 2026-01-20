#
# @lc app=leetcode id=2816 lang=python3
#
# [2816] Double a Number Represented as a Linked List
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # If the head is greater than 4, doubling it will result in a carry
        # that requires a new node at the front.
        if head.val > 4:
            head = ListNode(0, head)
        
        current = head
        while current:
            # Double the current value and take modulo 10
            current.val = (current.val * 2) % 10
            
            # Check if the next node will generate a carry
            # A carry is generated if the next node's value is > 4 (since 5*2=10)
            if current.next and current.next.val > 4:
                current.val += 1
            
            current = current.next
            
        return head
# @lc code=end