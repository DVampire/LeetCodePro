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
        // Build pattern from linked list
        vector<int> pat;
        for (ListNode* p = head; p; p = p->next) pat.push_back(p->val);
        int m = (int)pat.size();

        // Build LPS array (KMP prefix function)
        vector<int> lps(m, 0);
        for (int i = 1, len = 0; i < m; ) {
            if (pat[i] == pat[len]) {
                lps[i++] = ++len;
            } else if (len > 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        function<bool(TreeNode*, int)> dfs = [&](TreeNode* node, int j) -> bool {
            if (!node) return false;

            int x = node->val;
            while (j > 0 && pat[j] != x) j = lps[j - 1];
            if (pat[j] == x) ++j;
            if (j == m) return true;

            return dfs(node->left, j) || dfs(node->right, j);
        };

        return dfs(root, 0);
    }
};
# @lc code=end
