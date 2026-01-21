#
# @lc app=leetcode id=3579 lang=cpp
#
# [3579] Minimum Steps to Convert String with Operations
#
# @lc code=start
class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.length();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        // DP: dp[i] = min operations to transform word1[0..i-1] to word2[0..i-1]
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] != INT_MAX) {
                    string s1 = word1.substr(j, i - j);
                    string s2 = word2.substr(j, i - j);
                    int cost = minOpsForSubstring(s1, s2);
                    dp[i] = min(dp[i], dp[j] + cost);
                }
            }
        }
        
        return dp[n];
    }
    
private:
    // Calculate minimum operations for a single substring
    int minOpsForSubstring(string s1, string s2) {
        if (s1 == s2) return 0;
        
        // Try without reverse
        int cost1 = computeCost(s1, s2);
        
        // Try with reverse
        string s1_rev = s1;
        reverse(s1_rev.begin(), s1_rev.end());
        int cost2 = 1 + computeCost(s1_rev, s2);
        
        return min(cost1, cost2);
    }
    
    // Compute cost using swaps and replaces (no reverse)
    int computeCost(string s, string target) {
        int n = s.length();
        vector<bool> used(n, false);
        int ops = 0;
        
        // Greedily find beneficial swaps
        for (int i = 0; i < n; i++) {
            if (used[i] || s[i] == target[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (used[j] || s[j] == target[j]) continue;
                if (s[i] == target[j] && s[j] == target[i]) {
                    used[i] = used[j] = true;
                    ops++;
                    break;
                }
            }
        }
        
        // Replace remaining mismatches
        for (int i = 0; i < n; i++) {
            if (!used[i] && s[i] != target[i]) {
                ops++;
            }
        }
        
        return ops;
    }
};
# @lc code=end