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
        # If list has fewer than 3 nodes, no critical points possible
        if not head or not head.next or not head.next.next:
            return [-1, -1]
        
        # Store positions of critical points (1-indexed)
        critical_points = []
        
        # Pointers for traversal
        prev = head
        curr = head.next
        next_node = curr.next
        
        # Position counter (1-indexed)
        position = 2
        
        # Traverse the list
        while next_node:
            # Check if current node is a critical point
            if (curr.val > prev.val and curr.val > next_node.val) or \
               (curr.val < prev.val and curr.val < next_node.val):
                critical_points.append(position)
            
            # Move pointers forward
            prev = curr
            curr = next_node
            next_node = next_node.next
            position += 1
        
        # If fewer than 2 critical points, return [-1, -1]
        if len(critical_points) < 2:
            return [-1, -1]
        
        # Calculate minimum distance between consecutive critical points
        min_distance = float('inf')
        for i in range(1, len(critical_points)):
            min_distance = min(min_distance, critical_points[i] - critical_points[i-1])
        
        # Maximum distance is between first and last critical points
        max_distance = critical_points[-1] - critical_points[0]
        
        return [min_distance, max_distance]
# @lc code=end