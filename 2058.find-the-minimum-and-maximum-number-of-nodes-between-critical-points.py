#
# @lc app=leetcode id=2058 lang=python3
#
# [2058] Find the Minimum and Maximum Number of Nodes Between Critical Points
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
from typing import Optional, List

class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        # A critical point requires a previous and a next node.
        # The list must have at least 3 nodes to contain even one critical point.
        if not head or not head.next or not head.next.next:
            return [-1, -1]
        
        min_dist = float('inf')
        first_idx = -1
        prev_idx = -1
        
        # Start tracking from the second node (index 1)
        idx = 1
        prev_node = head
        curr_node = head.next
        
        while curr_node.next:
            next_node = curr_node.next
            
            # Check if curr_node is a local maxima or local minima
            is_maxima = curr_node.val > prev_node.val and curr_node.val > next_node.val
            is_minima = curr_node.val < prev_node.val and curr_node.val < next_node.val
            
            if is_maxima or is_minima:
                if first_idx == -1:
                    # First critical point found
                    first_idx = idx
                else:
                    # Calculate distance from the previous critical point found
                    # Minimum distance must be between two adjacent critical points
                    min_dist = min(min_dist, idx - prev_idx)
                
                # Update the index of the most recent critical point
                prev_idx = idx
            
            # Advance pointers
            prev_node = curr_node
            curr_node = next_node
            idx += 1
            
        # If min_dist was never updated, it means we found fewer than 2 critical points
        if min_dist == float('inf'):
            return [-1, -1]
        
        # Maximum distance is the distance between the first and the last critical point
        max_dist = prev_idx - first_idx
        
        return [int(min_dist), max_dist]
# @lc code=end