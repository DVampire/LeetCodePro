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
        
        # Helper function to check if the linked list matches a path starting from tree_node
        def check(list_node, tree_node):
            # If we reached the end of the list, we found a match
            if not list_node:
                return True
            # If we reached the end of the tree path before matching the list
            if not tree_node:
                return False
            # If values don't match, this path is invalid
            if list_node.val != tree_node.val:
                return False
            # Continue checking the rest of the list in both children
            return check(list_node.next, tree_node.left) or check(list_node.next, tree_node.right)
        
        # Iterative DFS to find the start node of the path in the tree
        stack = [root]
        while stack:
            node = stack.pop()
            
            # If current node value matches head, try to match the whole list
            if node.val == head.val and check(head, node):
                return True
            
            # Continue searching for the start of the list in children
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)
                
        return False
# @lc code=end