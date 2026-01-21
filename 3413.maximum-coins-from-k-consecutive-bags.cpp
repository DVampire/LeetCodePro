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
        
        set<long long> starts;
        for (const auto& seg : coins) {
            long long l = seg[0], r = seg[1];
            starts.insert(l);
            starts.insert(max(1LL, l - k + 1));
            starts.insert(max(1LL, r - k + 1));
        }
        
        long long maxCoins = 0;
        
        for (long long start : starts) {
            long long end = start + k - 1;
            long long totalCoins = 0;
            
            for (const auto& seg : coins) {
                long long l = seg[0], r = seg[1], c = seg[2];
                long long overlapStart = max(start, l);
                long long overlapEnd = min(end, r);
                
                if (overlapStart <= overlapEnd) {
                    totalCoins += (overlapEnd - overlapStart + 1) * c;
                }
            }
            
            maxCoins = max(maxCoins, totalCoins);
        }
        
        return maxCoins;
    }
};
# @lc code=end