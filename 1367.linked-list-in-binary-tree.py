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
        def check(h, r):
            if not h:
                return True
            if not r:
                return False
            if h.val != r.val:
                return False
            return check(h.next, r.left) or check(h.next, r.right)
        
        if not root:
            return False
            
        # Iterative DFS to visit every node in the tree
        stack = [root]
        while stack:
            node = stack.pop()
            # Check if linked list starts at the current tree node
            if check(head, node):
                return True
            # Push children to stack to continue searching
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)
        
        return False
# @lc code=end