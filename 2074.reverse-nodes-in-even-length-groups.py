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

from typing import Optional

class Solution:
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        prev = dummy
        group_len = 1
        while prev.next:
            cur = prev.next
            length = 0
            temp = cur
            group_tail = None
            while temp and length < group_len:
                group_tail = temp
                temp = temp.next
                length += 1
            if length % 2 == 0:
                reversed_head = None
                current = cur
                for _ in range(length):
                    next_node = current.next
                    current.next = reversed_head
                    reversed_head = current
                    current = next_node
                cur.next = temp
                prev.next = reversed_head
                prev = cur
            else:
                prev = group_tail
            group_len += 1
        return dummy.next
# @lc code=end
