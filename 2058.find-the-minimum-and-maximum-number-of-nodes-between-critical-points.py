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
        # A critical point requires a previous and a next node.
        # Thus, we need at least 3 nodes in the list.
        if not head or not head.next or not head.next.next:
            return [-1, -1]
        
        first_cp_idx = -1
        prev_cp_idx = -1
        min_dist = float('inf')
        
        # Start traversal from the second node (index 1)
        prev_val = head.val
        curr = head.next
        curr_idx = 1
        
        while curr.next:
            next_val = curr.next.val
            
            # Check if current node is local maxima or minima
            is_maxima = curr.val > prev_val and curr.val > next_val
            is_minima = curr.val < prev_val and curr.val < next_val
            
            if is_maxima or is_minima:
                if first_cp_idx == -1:
                    first_cp_idx = curr_idx
                else:
                    # Update minimum distance between consecutive critical points
                    min_dist = min(min_dist, curr_idx - prev_cp_idx)
                
                # Track the last critical point index found so far
                prev_cp_idx = curr_idx
            
            # Update pointers and index for the next iteration
            prev_val = curr.val
            curr = curr.next
            curr_idx += 1
        
        # If fewer than two critical points were found, min_dist remains infinity
        if min_dist == float('inf'):
            return [-1, -1]
        
        # Maximum distance is the distance between the first and last critical points
        max_dist = prev_cp_idx - first_cp_idx
        
        return [int(min_dist), max_dist]
# @lc code=end