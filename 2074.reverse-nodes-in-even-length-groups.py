#
# @lc app=leetcode id=2074 lang=python3
#
# [2074] Reverse Nodes in Even Length Groups
#

# @lc code=start
from typing import Optional

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def reverseEvenLengthGroups(self, head: Optional['ListNode']) -> Optional['ListNode']:
        def reverse_k(start: 'ListNode', k: int):
            prev = None
            cur = start
            for _ in range(k):
                nxt = cur.next
                cur.next = prev
                prev = cur
                cur = nxt
            # prev is new head, start is new tail
            return prev, start

        dummy = ListNode(0, head)
        prev = dummy
        curr = head
        group_size = 1

        while curr:
            # Find actual length of this group and the next group's start
            cnt = 0
            node = curr
            while node and cnt < group_size:
                node = node.next
                cnt += 1
            next_start = node

            if cnt % 2 == 0:
                new_head, new_tail = reverse_k(curr, cnt)
                prev.next = new_head
                new_tail.next = next_start
                prev = new_tail
                curr = next_start
            else:
                # No reversal; just advance prev and curr by cnt nodes
                for _ in range(cnt):
                    prev = curr
                    curr = curr.next

            group_size += 1

        return dummy.next
# @lc code=end
