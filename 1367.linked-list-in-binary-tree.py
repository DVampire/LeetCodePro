#
# @lc app=leetcode id=1367 lang=python3
#
# [1367] Linked List in Binary Tree
#

# @lc code=start
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        stack = [root]
        while stack:
            node = stack.pop()
            if not node:
                continue
            if self.match(head, node):
                return True
            stack.append(node.left)
            stack.append(node.right)
        return False
    
    def match(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        if not head:
            return True
        if not root:
            return False
        if head.val != root.val:
            return False
        return self.match(head.next, root.left) or self.match(head.next, root.right)
# @lc code=end