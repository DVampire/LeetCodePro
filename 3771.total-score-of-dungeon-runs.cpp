#
# @lc app=leetcode id=3771 lang=cpp
#
# [3771] Total Score of Dungeon Runs
#
# @lc code=start
class Solution {
public:
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        int n = damage.size();
        vector<long long> prefix(n + 1, 0);
        
        // Build prefix sum array
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + damage[i];
        }
        
        long long total = 0;
        
        // For each room i, count how many starting positions j earn a point at room i
        for (int i = 0; i < n; i++) {
            long long threshold = requirement[i] + prefix[i + 1] - hp;
            
            // Find the first j in [0, i] where prefix[j] >= threshold
            auto it = lower_bound(prefix.begin(), prefix.begin() + i + 1, threshold);
            int j = it - prefix.begin();
            
            // If such j exists within valid range, count starting positions from j to i
            if (j <= i) {
                total += (i - j + 1);
            }
        }
        
        return total;
    }
};
# @lc code=end