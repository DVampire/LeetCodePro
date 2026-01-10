#
# @lc app=leetcode id=2074 lang=python3
#
# [2074] Reverse Nodes in Even Length Groups
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
from typing import Optional

class Solution:
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head
        
        # The first group consists of only the head node (length 1, which is odd).
        # So we can start processing from the second group, with prev pointing to head.
        prev = head
        d = 2
        
        while prev.next:
            # Count actual nodes available in the current group
            count = 0
            temp = prev.next
            while count < d and temp:
                temp = temp.next
                count += 1
            
            if count % 2 == 0:
                # Record the start of the group to be reversed
                group_start = prev.next
                curr = group_start
                rev_prev = None
                
                # Standard in-place reversal for 'count' nodes
                for _ in range(count):
                    nxt = curr.next
                    curr.next = rev_prev
                    rev_prev = curr
                    curr = nxt
                
                # After reversal, rev_prev is the new head of the group,
                # group_start is the new tail, and curr is the node after the group.
                prev.next = rev_prev
                group_start.next = curr
                prev = group_start
            else:
                # If the actual count is odd, skip the group
                for _ in range(count):
                    prev = prev.next
            
            # Move to the next expected group size
            d += 1
            
        return head
# @lc code=end