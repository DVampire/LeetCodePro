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
        vector<long long> prefix_sum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix_sum[i + 1] = prefix_sum[i] + damage[i];
        }
        
        long long total = 0;
        for (int i = 0; i < n; i++) {
            // threshold = requirement[i] + prefix_sum[i+1] - hp
            // We need prefix_sum[j] >= threshold for j in [0, i]
            long long threshold = (long long)requirement[i] + prefix_sum[i + 1] - hp;
            
            // Binary search to find first j where prefix_sum[j] >= threshold
            auto it = lower_bound(prefix_sum.begin(), prefix_sum.begin() + i + 1, threshold);
            long long k = it - prefix_sum.begin();
            
            // Count of valid starting positions is (i + 1) - k
            total += (i + 1) - k;
        }
        
        return total;
    }
};
# @lc code=end