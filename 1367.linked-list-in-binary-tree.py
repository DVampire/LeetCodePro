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
        if not head:
            return True
        if not root:
            return False
        
        # Check if there's a path starting from current node
        # or check in left or right subtrees
        return (self.dfs(head, root) or 
                self.isSubPath(head, root.left) or 
                self.isSubPath(head, root.right))
    
    def dfs(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        # If we've reached the end of the linked list, we found a match
        if not head:
            return True
        # If we've reached the end of the tree path but not the list, no match
        if not root:
            return False
        
        # If current values don't match, no match
        if head.val != root.val:
            return False
        
        # Continue checking the next node in the list against children in the tree
        return (self.dfs(head.next, root.left) or 
                self.dfs(head.next, root.right))
# @lc code=end