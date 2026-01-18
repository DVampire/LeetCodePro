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
        if not head or not head.next:
            return head

        prev_group_tail = head
        curr = head.next
        expected_group_size = 2

        while curr:
            count = 0
            temp = curr
            while count < expected_group_size and temp:
                temp = temp.next
                count += 1

            if count % 2 == 0:
                node = curr
                prev = temp
                for _ in range(count):
                    nxt = node.next
                    node.next = prev
                    prev = node
                    node = nxt
                prev_group_tail.next = prev
                prev_group_tail = curr
                curr = temp
            else:
                for _ in range(count):
                    prev_group_tail = curr
                    curr = curr.next

            expected_group_size += 1

        return head
# @lc code=end