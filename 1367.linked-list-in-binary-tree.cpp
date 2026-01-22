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
        // Check if path starts at current root
        if (dfs(head, root)) return true;
        // Otherwise try left and right subtrees
        return isSubPath(head, root->left) || isSubPath(head, root->right);
    }
    
    // Helper to check if linked list matches starting at this tree node
    bool dfs(ListNode* head, TreeNode* root) {
        if (!head) return true; // All nodes matched
        if (!root) return false; // Tree ends before list ends
        if (head->val != root->val) return false;
        // Current values match, continue with next node in list and children
        return dfs(head->next, root->left) || dfs(head->next, root->right);
    }
};
# @lc code=end