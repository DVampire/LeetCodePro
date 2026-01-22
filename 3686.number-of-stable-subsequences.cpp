#
# @lc app=leetcode id=3686 lang=cpp
#
# [3686] Number of Stable Subsequences
#
# @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        const long long MOD = 1e9 + 7;
        // cnt[p][s] where p = parity (0 even, 1 odd)
        // s = 0 means streak of 1, s = 1 means streak of 2
        long long cnt[2][2] = {};
        
        for (int num : nums) {
            int p = num % 2;  // parity of current number
            int q = 1 - p;    // other parity
            
            // Save previous values before updating
            long long prev_p0 = cnt[p][0];
            long long prev_p1 = cnt[p][1];
            
            // Subsequences ending with parity p, streak 1:
            // - Previous subsequences (not extended)
            // - New single-element subsequence: +1
            // - Extend from different parity: cnt[q][0] + cnt[q][1]
            cnt[p][0] = (prev_p0 + 1 + cnt[q][0] + cnt[q][1]) % MOD;
            
            // Subsequences ending with parity p, streak 2:
            // - Previous subsequences (not extended)
            // - Extend from same parity streak 1
            cnt[p][1] = (prev_p1 + prev_p0) % MOD;
            
            // cnt[q][0] and cnt[q][1] remain unchanged
        }
        
        return (cnt[0][0] + cnt[0][1] + cnt[1][0] + cnt[1][1]) % MOD;
    }
};
# @lc code=end