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
        # Check if the path matches starting at the current node,
        # or if it exists starting from any node in the children subtrees.
        return self._dfs(head, root) or self.isSubPath(head, root.left) or self.isSubPath(head, root.right)

    def _dfs(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        # If the entire linked list has been traversed, we found a match.
        if not head:
            return True
        # If the tree ends before the linked list is finished, no match.
        if not root:
            return False
        # If values don't match, this specific downward path is invalid.
        if head.val != root.val:
            return False
        # Continue checking the next list node with both potential tree children.
        return self._dfs(head.next, root.left) or self._dfs(head.next, root.right)
# @lc code=end