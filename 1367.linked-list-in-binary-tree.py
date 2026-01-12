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
        if not root:
            return False
        
        # Check if the linked list starts at the current tree node,
        # or if it exists somewhere in the left or right subtrees.
        return self._checkPath(head, root) or \
               self.isSubPath(head, root.left) or \
               self.isSubPath(head, root.right)

    def _checkPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        # If we have reached the end of the linked list, it means the path exists.
        if not head:
            return True
        # If the tree path ends but the linked list hasn't, or values don't match.
        if not root or head.val != root.val:
            return False
        
        # Continue to check the next linked list node in the tree's children.
        return self._checkPath(head.next, root.left) or \
               self._checkPath(head.next, root.right)
# @lc code=end