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
        
        prev = head
        curr = head.next
        idx = 1
        
        while curr.next:
            val = curr.val
            p_val = prev.val
            n_val = curr.next.val
            
            # Check if current node is a critical point
            if (val > p_val and val > n_val) or (val < p_val and val < n_val):
                if first_idx == -1:
                    first_idx = idx
                else:
                    min_dist = min(min_dist, idx - last_idx)
                last_idx = idx
            
            prev = curr
            curr = curr.next
            idx += 1
            
        if min_dist == float('inf'):
            return [-1, -1]
            
        return [int(min_dist), last_idx - first_idx]
# @lc code=end