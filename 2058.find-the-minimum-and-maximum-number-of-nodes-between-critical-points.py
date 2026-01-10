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
class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        # A critical point needs a previous and a next node.
        # If the list has fewer than 3 nodes, no critical points are possible.
        if not head or not head.next or not head.next.next:
            return [-1, -1]
        
        first_cp_idx = -1
        prev_cp_idx = -1
        min_dist = float('inf')
        
        # Initialize traversal variables
        prev_val = head.val
        curr = head.next
        idx = 1
        
        # Iterate until the second-to-last node
        while curr.next:
            next_val = curr.next.val
            
            # Check if current node is a local maxima or minima
            is_maxima = curr.val > prev_val and curr.val > next_val
            is_minima = curr.val < prev_val and curr.val < next_val
            
            if is_maxima or is_minima:
                if first_cp_idx == -1:
                    # This is the first critical point we've encountered
                    first_cp_idx = idx
                else:
                    # Calculate distance from the previous critical point
                    min_dist = min(min_dist, idx - prev_cp_idx)
                
                # Update the index of the most recent critical point
                prev_cp_idx = idx
            
            # Move pointers forward
            prev_val = curr.val
            curr = curr.next
            idx += 1
            
        # If min_dist was never updated, we found fewer than 2 critical points
        if min_dist == float('inf'):
            return [-1, -1]
        
        # Maximum distance is always between the first and last critical point
        max_dist = prev_cp_idx - first_cp_idx
        
        return [int(min_dist), max_dist]
# @lc code=end