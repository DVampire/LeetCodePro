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
        
        def check(h, r):
            # If we've reached the end of the linked list, we found a match
            if not h:
                return True
            # If the tree ends before the list, no match
            if not r:
                return False
            # If values don't match, this path is invalid
            if h.val != r.val:
                return False
            # Recursively check the next list node in both child paths
            return check(h.next, r.left) or check(h.next, r.right)
        
        # Iterative DFS to explore every node in the tree as a potential starting point
        stack = [root]
        while stack:
            curr = stack.pop()
            if not curr:
                continue
            
            # Check if the list matches a path starting from the current node
            if check(head, curr):
                return True
            
            # Add children to the stack to check other potential starting points
            if curr.left:
                stack.append(curr.left)
            if curr.right:
                stack.append(curr.right)
                
        return False
# @lc code=end