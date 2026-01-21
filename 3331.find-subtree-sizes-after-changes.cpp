#
# @lc app=leetcode id=3331 lang=cpp
#
# [3331] Find Subtree Sizes After Changes
#
# @lc code=start
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<int> newParent = parent;
        
        // For each node from 1 to n-1, find its new parent
        for (int x = 1; x < n; x++) {
            // Traverse ancestors to find closest with same character
            int curr = parent[x];
            while (curr != -1) {
                if (s[curr] == s[x]) {
                    newParent[x] = curr;
                    break;
                }
                curr = parent[curr];
            }
        }
        
        // Build adjacency list for new tree
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) {
            children[newParent[i]].push_back(i);
        }
        
        // Calculate subtree sizes using DFS
        vector<int> answer(n);
        function<int(int)> dfs = [&](int node) -> int {
            int size = 1;
            for (int child : children[node]) {
                size += dfs(child);
            }
            return answer[node] = size;
        };
        
        dfs(0);
        return answer;
    }
};
# @lc code=end