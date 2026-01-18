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
        # If the head value is 5 or more, doubling it will create a new carry digit (1) at the front.
        # We can handle this by adding a dummy node with value 0 before the head.
        if head.val >= 5:
            head = ListNode(0, head)
        
        curr = head
        while curr:
            # Double the current node's value and keep only the last digit.
            # (Even if we add a carry later, the value will not exceed 9 because (8 + 1) is the max).
            curr.val = (curr.val * 2) % 10
            
            # If the next node's value is 5 or greater, it will produce a carry for the current node.
            if curr.next and curr.next.val >= 5:
                curr.val += 1
            
            curr = curr.next
            
        return head
# @lc code=end