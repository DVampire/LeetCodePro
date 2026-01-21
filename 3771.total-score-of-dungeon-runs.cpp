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
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + damage[i - 1];
        }
        long long total = 0;
        for (int k = 1; k <= n; ++k) {
            long long T = (long long)requirement[k - 1] + prefix[k] - hp;
            auto it = lower_bound(prefix.begin(), prefix.begin() + k, T);
            int idx = it - prefix.begin();
            if (idx < k) {
                total += (k - idx);
            }
        }
        return total;
    }
};
# @lc code=end