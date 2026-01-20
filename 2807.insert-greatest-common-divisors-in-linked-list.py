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
        # If the list has 0 or 1 node, no insertion is needed.
        if not head or not head.next:
            return head
        
        current = head
        # Iterate while there is a next node to form a pair
        while current and current.next:
            val1 = current.val
            val2 = current.next.val
            
            # Calculate GCD
            gcd_val = math.gcd(val1, val2)
            
            # Create new node with GCD value
            new_node = ListNode(gcd_val)
            
            # Insert new_node between current and current.next
            new_node.next = current.next
            current.next = new_node
            
            # Move current pointer to the next original node
            # We skip the node we just inserted
            current = new_node.next
            
        return head
# @lc code=end