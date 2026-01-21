#
# @lc app=leetcode id=3413 lang=cpp
#
# [3413] Maximum Coins From K Consecutive Bags
#
# @lc code=start
class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        // Sort segments by starting position
        sort(coins.begin(), coins.end());
        
        long long maxCoins = 0;
        
        // Collect all meaningful starting positions
        set<long long> starts;
        starts.insert(1); // Consider starting from the beginning
        
        for (auto& seg : coins) {
            long long l = seg[0], r = seg[1];
            starts.insert(l); // Window starts at segment start
            long long endStart = r - k + 1;
            if (endStart >= 1) {
                starts.insert(endStart); // Window ends at segment end
            }
        }
        
        // For each starting position, calculate total coins
        for (long long start : starts) {
            long long end = start + k - 1;
            long long total = 0;
            
            for (auto& seg : coins) {
                long long l = seg[0], r = seg[1], c = seg[2];
                // Calculate overlap between [start, end] and [l, r]
                long long overlapStart = max(l, start);
                long long overlapEnd = min(r, end);
                if (overlapStart <= overlapEnd) {
                    total += (overlapEnd - overlapStart + 1) * c;
                }
            }
            
            maxCoins = max(maxCoins, total);
        }
        
        return maxCoins;
    }
};
# @lc code=end