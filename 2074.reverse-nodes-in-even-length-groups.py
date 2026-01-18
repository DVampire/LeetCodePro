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
        prev = head
        group_size = 2
        
        while prev.next:
            # Count actual nodes in current group
            node = prev.next
            count = 0
            while count < group_size and node:
                count += 1
                node = node.next
            
            if count % 2 == 0:
                # Reverse the group
                curr = prev.next
                reverse_prev = None
                for _ in range(count):
                    nxt = curr.next
                    curr.next = reverse_prev
                    reverse_prev = curr
                    curr = nxt
                
                # Reconnect the reversed segment
                tail = prev.next
                prev.next = reverse_prev
                tail.next = curr
                prev = tail
            else:
                # Skip the group
                for _ in range(count):
                    prev = prev.next
            
            group_size += 1
            
        return head
# @lc code=end