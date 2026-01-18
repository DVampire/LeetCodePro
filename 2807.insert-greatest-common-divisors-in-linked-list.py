#
# @lc app=leetcode id=2807 lang=python3
#
# [2807] Insert Greatest Common Divisors in Linked List
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
import math

class Solution:
    def insertGreatestCommonDivisors(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head
        
        current = head
        while current and current.next:
            # Calculate the GCD of the current node and the next node
            gcd_val = math.gcd(current.val, current.next.val)
            
            # Create a new node with the GCD value
            new_node = ListNode(gcd_val)
            
            # Insert the new node between current and current.next
            new_node.next = current.next
            current.next = new_node
            
            # Move the pointer forward by two steps to the original next node
            current = new_node.next
            
        return head
# @lc code=end