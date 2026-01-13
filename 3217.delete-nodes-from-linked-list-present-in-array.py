#
# @lc app=leetcode id=3217 lang=python3
#
# [3217] Delete Nodes From Linked List Present in Array
#

from typing import List, Optional

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def modifiedList(self, nums: List[int], head: Optional['ListNode']) -> Optional['ListNode']:
        to_delete = set(nums)

        dummy = ListNode(0, head)
        cur = dummy

        while cur.next:
            if cur.next.val in to_delete:
                cur.next = cur.next.next
            else:
                cur = cur.next

        return dummy.next
# @lc code=end
