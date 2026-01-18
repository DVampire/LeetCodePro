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
        
        # Use a dummy node to handle deletions at the head easily
        dummy = ListNode(0)
        dummy.next = head
        
        current = dummy
        while current.next:
            if current.next.val in nums_set:
                # Delete the node by skipping it
                current.next = current.next.next
            else:
                # Only move current forward if we didn't delete a node
                current = current.next
        
        return dummy.next
# @lc code=end