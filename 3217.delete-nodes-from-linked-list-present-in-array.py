#
# @lc app=leetcode id=3217 lang=python3
#
# [3217] Delete Nodes From Linked List Present in Array
#
# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def modifiedList(self, nums: List[int], head: Optional[ListNode]) -> Optional[ListNode]:
        # Convert nums to a set for O(1) lookup
        nums_set = set(nums)
        
        # Create a dummy node to handle edge cases
        dummy = ListNode(0)
        dummy.next = head
        
        # Use prev to track the previous node
        prev = dummy
        current = head
        
        while current:
            if current.val in nums_set:
                # Remove this node by skipping it
                prev.next = current.next
            else:
                # Keep this node, move prev forward
                prev = current
            current = current.next
        
        return dummy.next
# @lc code=end