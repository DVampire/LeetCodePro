#
# @lc app=leetcode id=3575 lang=cpp
#
# [3575] Maximum Good Subtree Score
#
# @lc code=start
class Solution {
public:
    const int MOD = 1e9 + 7;
    
    int getMask(int val) {
        int mask = 0;
        while (val > 0) {
            int digit = val % 10;
            if (mask & (1 << digit)) {
                return -1;
            }
            mask |= (1 << digit);
            val /= 10;
        }
        return mask;
    }
    
    bool hasConflict(int mask1, int mask2) {
        return (mask1 & mask2) != 0;
    }
    
    unordered_map<int, long long> dfs(int node, vector<vector<int>>& children, vector<int>& vals, vector<long long>& maxScore) {
        unordered_map<int, long long> dp;
        dp[0] = 0;
        
        for (int child : children[node]) {
            unordered_map<int, long long> childDp = dfs(child, children, vals, maxScore);
            
            unordered_map<int, long long> newDp;
            for (auto& [mask1, sum1] : dp) {
                for (auto& [mask2, sum2] : childDp) {
                    if (!hasConflict(mask1, mask2)) {
                        int newMask = mask1 | mask2;
                        newDp[newMask] = max(newDp[newMask], sum1 + sum2);
                    }
                }
            }
            dp = newDp;
        }
        
        int nodeMask = getMask(vals[node]);
        if (nodeMask != -1) {
            unordered_map<int, long long> newDp = dp;
            for (auto& [mask, sum] : dp) {
                if (!hasConflict(mask, nodeMask)) {
                    int newMask = mask | nodeMask;
                    newDp[newMask] = max(newDp[newMask], sum + vals[node]);
                }
            }
            dp = newDp;
        }
        
        long long maxSum = 0;
        for (auto& [mask, sum] : dp) {
            maxSum = max(maxSum, sum);
        }
        maxScore[node] = maxSum;
        
        return dp;
    }
    
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size();
        vector<vector<int>> children(n);
        
        for (int i = 1; i < n; i++) {
            children[par[i]].push_back(i);
        }
        
        vector<long long> maxScore(n);
        dfs(0, children, vals, maxScore);
        
        long long result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + maxScore[i]) % MOD;
        }
        
        return result;
    }
};
# @lc code=end