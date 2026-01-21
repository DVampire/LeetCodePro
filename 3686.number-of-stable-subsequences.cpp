#
# @lc app=leetcode id=3686 lang=cpp
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        int n = nums.size();
        const int MOD = 1000000007;
        long long prev[3][2] = {{0, 0}, {0, 0}, {0, 0}};
        for (int i = 0; i < n; i++) {
            int cur_p = nums[i] & 1;
            long long curr[3][2] = {{0, 0}, {0, 0}, {0, 0}};
            // not take: carry over
            for (int k = 1; k <= 2; k++) {
                for (int p = 0; p < 2; p++) {
                    curr[k][p] = (curr[k][p] + prev[k][p]) % MOD;
                }
            }
            // take from empty
            curr[1][cur_p] = (curr[1][cur_p] + 1) % MOD;
            // take from previous non-empty
            for (int pk = 1; pk <= 2; pk++) {
                for (int pp = 0; pp < 2; pp++) {
                    long long ways = prev[pk][pp];
                    if (ways == 0) continue;
                    if (pp == cur_p) {
                        int nk = pk + 1;
                        if (nk <= 2) {
                            curr[nk][cur_p] = (curr[nk][cur_p] + ways) % MOD;
                        }
                    } else {
                        curr[1][cur_p] = (curr[1][cur_p] + ways) % MOD;
                    }
                }
            }
            // copy curr to prev
            for (int k = 1; k <= 2; k++) {
                for (int p = 0; p < 2; p++) {
                    prev[k][p] = curr[k][p];
                }
            }
        }
        long long total = 0;
        for (int k = 1; k <= 2; k++) {
            for (int p = 0; p < 2; p++) {
                total = (total + prev[k][p]) % MOD;
            }
        }
        return total;
    }
};
# @lc code=end
