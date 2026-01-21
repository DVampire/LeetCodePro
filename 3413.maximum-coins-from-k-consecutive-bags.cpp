#
# @lc app=leetcode id=3413 lang=cpp
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        sort(coins.begin(), coins.end());
        
        int n = coins.size();
        long long maxCoins = 0;
        
        // Precompute prefix sums
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + (long long)(coins[i][1] - coins[i][0] + 1) * coins[i][2];
        }
        
        // Case 1: Window starts at left boundary of segment i
        for (int i = 0; i < n; i++) {
            long long windowEnd = (long long)coins[i][0] + k - 1;
            
            // Find rightmost segment with start <= windowEnd
            int lo = i, hi = n - 1, lastSeg = i;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (coins[mid][0] <= windowEnd) {
                    lastSeg = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            
            long long total = prefixSum[lastSeg] - prefixSum[i];
            long long partialEnd = min(windowEnd, (long long)coins[lastSeg][1]);
            total += (partialEnd - coins[lastSeg][0] + 1) * coins[lastSeg][2];
            
            maxCoins = max(maxCoins, total);
        }
        
        // Case 2: Window ends at right boundary of segment i
        for (int i = 0; i < n; i++) {
            long long windowStart = (long long)coins[i][1] - k + 1;
            
            // Find leftmost segment with end >= windowStart
            int lo = 0, hi = i, firstSeg = i;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (coins[mid][1] >= windowStart) {
                    firstSeg = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            
            long long total = prefixSum[i + 1] - prefixSum[firstSeg + 1];
            long long partialStart = max(windowStart, (long long)coins[firstSeg][0]);
            total += (coins[firstSeg][1] - partialStart + 1) * coins[firstSeg][2];
            
            maxCoins = max(maxCoins, total);
        }
        
        return maxCoins;
    }
};
# @lc code=end