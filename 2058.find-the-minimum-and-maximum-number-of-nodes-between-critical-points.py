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

from typing import Optional, List

class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        critical = []
        if not head or not head.next:
            return [-1, -1]
        prev = head
        cur = head.next
        pos = 2
        while cur.next:
            nxt = cur.next
            if (cur.val > prev.val and cur.val > nxt.val) or \
               (cur.val < prev.val and cur.val < nxt.val):
                critical.append(pos)
            prev = cur
            cur = nxt
            pos += 1
        if len(critical) < 2:
            return [-1, -1]
        min_d = float('inf')
        for j in range(1, len(critical)):
            d = critical[j] - critical[j - 1]
            min_d = min(min_d, d)
        max_d = critical[-1] - critical[0]
        return [min_d, max_d]

# @lc code=end