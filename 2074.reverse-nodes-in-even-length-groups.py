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
        prev_group_end = head
        group_len = 2
        
        while prev_group_end.next:
            # Determine actual length of the current group
            curr = prev_group_end.next
            actual_len = 0
            temp = curr
            while temp and actual_len < group_len:
                temp = temp.next
                actual_len += 1
            
            if actual_len % 2 == 0:
                # Reverse the current group
                reverse_prev = None
                reverse_curr = curr
                for _ in range(actual_len):
                    next_node = reverse_curr.next
                    reverse_curr.next = reverse_prev
                    reverse_prev = reverse_curr
                    reverse_curr = next_node
                
                # Reconnect the reversed segment
                # curr is now the end of the reversed group
                # reverse_prev is the new head of the group
                # reverse_curr is the start of the next group
                prev_group_end.next = reverse_prev
                curr.next = reverse_curr
                prev_group_end = curr
            else:
                # Skip the current group
                for _ in range(actual_len):
                    prev_group_end = prev_group_end.next
            
            group_len += 1
            
        return head
# @lc code=end