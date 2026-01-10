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
        
        # Check if the path starts at the current root, or in the left/right subtrees.
        if self.dfs(head, root):
            return True
        
        return self.isSubPath(head, root.left) or self.isSubPath(head, root.right)

    def dfs(self, head: Optional[ListNode], node: Optional[TreeNode]) -> bool:
        # If we reached the end of the linked list, we found a match.
        if not head:
            return True
        # If we reached a leaf in the tree but the list isn't finished, no match.
        if not node:
            return False
        # If values don't match, this path is not valid.
        if head.val != node.val:
            return False
        
        # Continue checking the next node in the list with the left and right children.
        return self.dfs(head.next, node.left) or self.dfs(head.next, node.right)
# @lc code=end