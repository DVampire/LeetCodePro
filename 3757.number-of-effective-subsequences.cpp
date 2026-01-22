#
# @lc app=leetcode id=3757 lang=cpp
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
class Solution {
public:
    int countEffective(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        
        // Compute full OR
        int full_or = 0;
        for (int x : nums) full_or |= x;
        
        // Find bits in full_or
        vector<int> bits;
        for (int i = 0; i < 20; i++) {
            if (full_or & (1 << i)) bits.push_back(i);
        }
        int k = bits.size();
        
        // Compress nums[i] to indices and count
        vector<int> cnt(1 << k, 0);
        for (int x : nums) {
            int idx = 0;
            for (int i = 0; i < k; i++) {
                if (x & (1 << bits[i])) {
                    idx |= (1 << i);
                }
            }
            cnt[idx]++;
        }
        
        // SOS DP: dp[mask] = sum of cnt[v] for all v that are subsets of mask
        vector<int> dp = cnt;
        for (int i = 0; i < k; i++) {
            for (int mask = 0; mask < (1 << k); mask++) {
                if (mask & (1 << i)) {
                    dp[mask] += dp[mask ^ (1 << i)];
                }
            }
        }
        
        // Precompute powers of 2
        vector<long long> pow2(n + 1);
        pow2[0] = 1;
        for (int i = 1; i <= n; i++) {
            pow2[i] = pow2[i-1] * 2 % MOD;
        }
        
        // Inclusion-exclusion
        long long ans = 0;
        int full_mask = (1 << k) - 1;
        for (int sub = 1; sub <= full_mask; sub++) {
            int complement = full_mask ^ sub;
            int union_cnt = n - dp[complement];
            long long contribution = pow2[n - union_cnt];
            if (__builtin_popcount(sub) % 2 == 1) {
                ans = (ans + contribution) % MOD;
            } else {
                ans = (ans - contribution + MOD) % MOD;
            }
        }
        
        return (int)ans;
    }
};
# @lc code=end