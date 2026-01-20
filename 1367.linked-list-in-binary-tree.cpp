#
# @lc app=leetcode id=1367 lang=cpp
#
# [1367] Linked List in Binary Tree
#

# @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (!root) return false;
        // Check if the path starts at the current root, or in the left/right subtrees.
        return checkPath(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }

private:
    bool checkPath(ListNode* head, TreeNode* node) {
        // If we reached the end of the linked list, we found a match.
        if (!head) return true;
        // If we reached the end of a tree path without finishing the list, no match.
        if (!node) return false;
        // If values don't match, this path is invalid.
        if (head->val != node->val) return false;
        
        // Continue matching the next list node with the tree's children.
        return checkPath(head->next, node->left) || checkPath(head->next, node->right);
    }
};
# @lc code=end