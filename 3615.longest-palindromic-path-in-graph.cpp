#
# @lc app=leetcode id=3615 lang=cpp
#
# [3615] Longest Palindromic Path in Graph
#
# @lc code=start
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        vector<vector<pair<int, int>>> states(1 << n);
        vector<vector<vector<bool>>> dp(1 << n, vector<vector<bool>>(n, vector<bool>(n, false)));
        
        auto addState = [&](int mask, int i, int j) {
            if (!dp[mask][i][j]) {
                dp[mask][i][j] = true;
                states[mask].push_back({i, j});
            }
        };
        
        int ans = 1;
        
        // Base case: single nodes (palindrome of length 1)
        for (int i = 0; i < n; i++) {
            addState(1 << i, i, i);
        }
        
        // Base case: two adjacent nodes with same label (palindrome of length 2)
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                if (label[i] == label[j]) {
                    addState((1 << i) | (1 << j), i, j);
                    ans = 2;
                }
            }
        }
        
        // Extend palindromes by adding matching pairs at both ends
        for (int mask = 1; mask < (1 << n); mask++) {
            for (auto& [i, j] : states[mask]) {
                for (int u : adj[i]) {
                    if (mask & (1 << u)) continue;
                    for (int v : adj[j]) {
                        if (mask & (1 << v)) continue;
                        if (u == v) continue;
                        if (label[u] != label[v]) continue;
                        
                        int newMask = mask | (1 << u) | (1 << v);
                        addState(newMask, u, v);
                        ans = max(ans, __builtin_popcount(newMask));
                    }
                }
            }
        }
        
        return ans;
    }
};
# @lc code=end