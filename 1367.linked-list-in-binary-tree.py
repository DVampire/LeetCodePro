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
        def check(h: Optional[ListNode], n: Optional[TreeNode]) -> bool:
            # If we've matched all nodes in the linked list
            if not h:
                return True
            # If we reached the end of a tree path but list isn't finished
            if not n:
                return False
            # If values don't match, this path is not valid
            if h.val != n.val:
                return False
            # Recursively check the next list node in both children
            return check(h.next, n.left) or check(h.next, n.right)
        
        if not root:
            return False
        
        # Standard iterative DFS to visit every node in the tree as a potential start
        stack = [root]
        while stack:
            curr = stack.pop()
            if not curr:
                continue
            
            # If the current tree node matches the head of the list, try matching the rest
            if curr.val == head.val:
                if check(head, curr):
                    return True
            
            # Add children to stack to continue outer search
            if curr.left:
                stack.append(curr.left)
            if curr.right:
                stack.append(curr.right)
                
        return False
# @lc code=end