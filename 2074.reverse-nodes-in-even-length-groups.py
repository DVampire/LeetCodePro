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
class Solution:
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        prev_group_end = dummy
        group_size = 1
        
        while prev_group_end.next:
            # Count actual nodes in current group
            group_start = prev_group_end.next
            count = 0
            current = group_start
            
            # Count up to group_size nodes or until end
            while current and count < group_size:
                current = current.next
                count += 1
            
            # If count is even, reverse this group
            if count % 2 == 0:
                # Reverse the group
                prev = current  # This is the node after the group
                curr = group_start
                for _ in range(count):
                    next_node = curr.next
                    curr.next = prev
                    prev = curr
                    curr = next_node
                
                # Connect the reversed group
                prev_group_end.next = prev
                prev_group_end = group_start
            else:
                # Move prev_group_end to the end of this group
                for _ in range(count):
                    prev_group_end = prev_group_end.next
            
            group_size += 1
        
        return dummy.next
# @lc code=end