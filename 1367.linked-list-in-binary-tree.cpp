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
        // Check if the path starts at the current root, 
        // or if it exists in the left or right subtrees.
        return isMatch(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }

private:
    bool isMatch(ListNode* head, TreeNode* root) {
        // If we reached the end of the list, we found a match.
        if (!head) return true;
        // If we reached a leaf in the tree but the list isn't finished, no match.
        if (!root) return false;
        // If values don't match, this path is invalid.
        if (head->val != root->val) return false;
        
        // Continue matching the next list element in either the left or right child.
        return isMatch(head->next, root->left) || isMatch(head->next, root->right);
    }
};
# @lc code=end