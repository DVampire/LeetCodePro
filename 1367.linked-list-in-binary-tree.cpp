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
        auto match = [&](auto&& self, ListNode* list, TreeNode* tree) -> bool {
            if (!list) return true;
            if (!tree || list->val != tree->val) return false;
            return self(self, list->next, tree->left) || self(self, list->next, tree->right);
        };
        auto traverse = [&](auto&& self, TreeNode* node, ListNode* listHead) -> bool {
            if (!node) return false;
            if (match(match, listHead, node)) return true;
            return self(self, node->left, listHead) || self(self, node->right, listHead);
        };
        return traverse(traverse, root, head);
    }
};
# @lc code=end