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
        if not head:
            return None
        
        prev = head
        group_len = 2
        
        while prev.next:
            # Count the actual number of nodes in the current group
            count = 0
            curr = prev.next
            temp = curr
            while temp and count < group_len:
                count += 1
                temp = temp.next
            
            if count % 2 == 0:
                # If the actual group length is even, reverse the group
                p = None
                node = curr
                for _ in range(count):
                    nxt = node.next
                    node.next = p
                    p = node
                    node = nxt
                
                # Reconnect the reversed segment back into the list
                # prev -> p (new head) ... curr (new tail) -> node (next group)
                prev.next = p
                curr.next = node
                prev = curr
            else:
                # If the actual group length is odd, skip the group
                for _ in range(count):
                    prev = prev.next
            
            group_len += 1
            
        return head
# @lc code=end