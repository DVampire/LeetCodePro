#
# @lc app=leetcode id=3743 lang=cpp
#
# [3743] Maximize Cyclic Partition Score
#
# @lc code=start
class Solution {
public:
    long long maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        long long maxScore = 0;
        
        // Try each starting position in the cyclic array
        for (int start = 0; start < n; start++) {
            // Create a linear array starting from 'start'
            vector<int> arr(n);
            for (int i = 0; i < n; i++) {
                arr[i] = nums[(start + i) % n];
            }
            
            // Precompute min and max for all ranges [i, j]
            vector<vector<int>> minVal(n, vector<int>(n));
            vector<vector<int>> maxVal(n, vector<int>(n));
            for (int i = 0; i < n; i++) {
                minVal[i][i] = maxVal[i][i] = arr[i];
                for (int j = i + 1; j < n; j++) {
                    minVal[i][j] = min(minVal[i][j-1], arr[j]);
                    maxVal[i][j] = max(maxVal[i][j-1], arr[j]);
                }
            }
            
            // DP to partition arr into at most k parts
            // dp[i][j] = max score to partition arr[0..i-1] into exactly j parts
            vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, -1));
            dp[0][0] = 0;
            
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= min(i, k); j++) {
                    // Try all possible start positions for the j-th segment
                    for (int p = j - 1; p < i; p++) {
                        if (dp[p][j-1] == -1) continue;
                        
                        // Segment from arr[p] to arr[i-1]
                        long long range = (long long)maxVal[p][i-1] - minVal[p][i-1];
                        if (dp[i][j] == -1) {
                            dp[i][j] = dp[p][j-1] + range;
                        } else {
                            dp[i][j] = max(dp[i][j], dp[p][j-1] + range);
                        }
                    }
                }
            }
            
            // Take the maximum score using at most k segments
            for (int j = 1; j <= k; j++) {
                if (dp[n][j] != -1) {
                    maxScore = max(maxScore, dp[n][j]);
                }
            }
        }
        
        return maxScore;
    }
};
# @lc code=end