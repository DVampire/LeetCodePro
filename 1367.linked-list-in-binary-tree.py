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
        
        # Check if the path starts at the current root
        if self.checkPath(head, root):
            return True
        
        # Otherwise, check if the path starts in the left or right subtree
        return self.isSubPath(head, root.left) or self.isSubPath(head, root.right)

    def checkPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        # If we reached the end of the linked list, we found a match
        if not head:
            return True
        # If we reached the end of the tree path before the list, no match
        if not root:
            return False
        # If values don't match, this path is invalid
        if head.val != root.val:
            return False
        
        # Continue checking the rest of the list in the children
        return self.checkPath(head.next, root.left) or self.checkPath(head.next, root.right)
# @lc code=end