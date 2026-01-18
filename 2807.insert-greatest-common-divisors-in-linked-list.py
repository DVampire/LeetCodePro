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
from typing import Optional

class Solution:
    def insertGreatestCommonDivisors(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head
        
        curr = head
        while curr and curr.next:
            # Calculate GCD of current node and next node
            gcd_val = math.gcd(curr.val, curr.next.val)
            
            # Create the new node
            new_node = ListNode(gcd_val)
            
            # Insert new_node between curr and curr.next
            new_node.next = curr.next
            curr.next = new_node
            
            # Move curr to the original next node, which is now new_node.next
            curr = new_node.next
            
        return head
# @lc code=end