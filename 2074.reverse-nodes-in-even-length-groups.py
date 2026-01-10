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
        # The first group always has length 1 (odd), so it's never reversed.
        # We start our traversal from the node immediately after the first group.
        prev = head
        group_size = 2
        
        while prev.next:
            # Count the actual number of nodes in the current group
            node = prev.next
            count = 0
            while node and count < group_size:
                count += 1
                node = node.next
            
            # If the actual count is even, reverse the group
            if count % 2 == 0:
                curr = prev.next
                # 'node' is currently pointing to the start of the next group.
                # By initializing 'rev_prev' to 'node', the tail of our reversed
                # segment will automatically point to the next group.
                rev_prev = node
                for _ in range(count):
                    tmp = curr.next
                    curr.next = rev_prev
                    rev_prev = curr
                    curr = tmp
                
                # Connect the previous part of the list to the new head of the reversed group.
                # The original head of this group is now the tail.
                old_head = prev.next
                prev.next = rev_prev
                prev = old_head
            else:
                # If the count is odd, skip the nodes in this group.
                for _ in range(count):
                    prev = prev.next
            
            # Increment target group size for the next natural number group
            group_size += 1
            
        return head
# @lc code=end