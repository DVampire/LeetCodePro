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
        // Try to match starting from current node, or try left/right subtrees
        return match(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }
    
private:
    bool match(ListNode* head, TreeNode* root) {
        // Successfully matched the entire list
        if (!head) return true;
        // Reached end of tree path without matching
        if (!root) return false;
        // Values don't match
        if (head->val != root->val) return false;
        // Continue matching with next list node and either left or right child
        return match(head->next, root->left) || match(head->next, root->right);
    }
};
# @lc code=end