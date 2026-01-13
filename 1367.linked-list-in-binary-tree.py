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
        # Helper function to check if linked list matches from current tree node going downward
        def matches(list_node, tree_node):
            # If we've matched the entire linked list
            if not list_node:
                return True
            # If tree ended but list hasn't
            if not tree_node:
                return False
            # If values don't match
            if list_node.val != tree_node.val:
                return False
            # Try matching in left or right subtree (continuing downward)
            return matches(list_node.next, tree_node.left) or matches(list_node.next, tree_node.right)
        
        # Base case: empty tree
        if not root:
            return False
        
        # Try starting from current node, or try starting from left/right subtrees
        return matches(head, root) or self.isSubPath(head, root.left) or self.isSubPath(head, root.right)
# @lc code=end