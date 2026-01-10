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
        def check(lnode, tnode):
            # If we've reached the end of the linked list, the path is found
            if not lnode:
                return True
            # If we've reached a null tree node before finishing the list, no match
            if not tnode:
                return False
            # If the current values don't match, this is not the path
            if lnode.val != tnode.val:
                return False
            # Continue checking the next list node in both children of the tree node
            return check(lnode.next, tnode.left) or check(lnode.next, tnode.right)

        if not root:
            return False

        # Use an iterative DFS to traverse every node in the binary tree
        # This avoids potential RecursionError on skewed trees with up to 2500 nodes
        stack = [root]
        while stack:
            curr = stack.pop()
            # Check if the linked list sequence starts at the current tree node
            if check(head, curr):
                return True
            # Add children to the stack to continue tree traversal
            if curr.left:
                stack.append(curr.left)
            if curr.right:
                stack.append(curr.right)
        
        return False
# @lc code=end