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
        # The constraints state there are at least 2 nodes.
        if not head or not head.next or not head.next.next:
            return [-1, -1]
        
        first_cp_idx = -1
        last_cp_idx = -1
        min_dist = float('inf')
        
        prev_node = head
        curr_node = head.next
        curr_idx = 1
        
        while curr_node.next:
            next_node = curr_node.next
            
            # Check if current node is a local maxima or local minima
            is_maxima = curr_node.val > prev_node.val and curr_node.val > next_node.val
            is_minima = curr_node.val < prev_node.val and curr_node.val < next_node.val
            
            if is_maxima or is_minima:
                if first_cp_idx == -1:
                    first_cp_idx = curr_idx
                else:
                    # Update the minimum distance between adjacent critical points
                    current_dist = curr_idx - last_cp_idx
                    if current_dist < min_dist:
                        min_dist = current_dist
                
                # Update the most recent critical point index
                last_cp_idx = curr_idx
            
            # Move pointers forward
            prev_node = curr_node
            curr_node = next_node
            curr_idx += 1
            
        # If we found fewer than two critical points
        if min_dist == float('inf'):
            return [-1, -1]
        
        # The maximum distance is between the first and last critical points
        max_dist = last_cp_idx - first_cp_idx
        
        return [int(min_dist), max_dist]
# @lc code=end