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
        if not head or not head.next or not head.next.next:
            return [-1, -1]
        
        first_idx = -1
        last_idx = -1
        min_dist = float('inf')
        
        prev_val = head.val
        curr = head.next
        i = 1 # Index of curr node
        
        while curr.next:
            next_val = curr.next.val
            
            # Check if current node is a critical point
            is_maxima = curr.val > prev_val and curr.val > next_val
            is_minima = curr.val < prev_val and curr.val < next_val
            
            if is_maxima or is_minima:
                if first_idx == -1:
                    first_idx = i
                else:
                    min_dist = min(min_dist, i - last_idx)
                
                last_idx = i
            
            # Move to next node
            prev_val = curr.val
            curr = curr.next
            i += 1
            
        if first_idx == last_idx:
            # Only one critical point found
            return [-1, -1]
            
        return [int(min_dist), last_idx - first_idx]

# @lc code=end