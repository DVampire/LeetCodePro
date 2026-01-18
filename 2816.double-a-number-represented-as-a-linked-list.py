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
        # If the head value is 5 or more, doubling it will result in a carry.
        # We can handle this by adding a dummy node with value 0 at the front.
        if head.val >= 5:
            head = ListNode(0, head)
        
        curr = head
        while curr:
            # The new value of the current node is (original_val * 2) % 10.
            # However, we must also add the carry from the next node.
            # A carry is produced if the next node's value is 5 or greater.
            new_val = (curr.val * 2) % 10
            
            if curr.next and curr.next.val >= 5:
                new_val += 1
            
            curr.val = new_val
            curr = curr.next
            
        return head
# @lc code=end