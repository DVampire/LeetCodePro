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
        
        # Check if the linked list starts at the current tree node
        if self._dfs(head, root):
            return True
        
        # Otherwise, recursively check the left and right subtrees
        return self.isSubPath(head, root.left) or self.isSubPath(head, root.right)

    def _dfs(self, head: Optional[ListNode], node: Optional[TreeNode]) -> bool:
        # If we have matched all nodes in the linked list
        if not head:
            return True
        # If we reach the end of a tree path but the linked list isn't finished
        if not node:
            return False
        # If values do not match, this path is invalid
        if head.val != node.val:
            return False
        
        # Continue matching the next linked list node in either the left or right child
        return self._dfs(head.next, node.left) or self._dfs(head.next, node.right)
# @lc code=end