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
        def check(node: Optional[TreeNode], ln: Optional[ListNode]) -> bool:
            if not ln:
                return True
            if not node or node.val != ln.val:
                return False
            return check(node.left, ln.next) or check(node.right, ln.next)
        
        def dfs(node: Optional[TreeNode]) -> bool:
            if not node:
                return False
            if check(node, head):
                return True
            return dfs(node.left) or dfs(node.right)
        
        return dfs(root)
# @lc code=end