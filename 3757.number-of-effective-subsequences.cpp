#
# @lc app=leetcode id=3757 lang=cpp
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
class Solution {
public:
    int countEffective(vector<int>& nums) {
        int n = nums.size();
        int total_or = 0;
        for (int x : nums) total_or |= x;

        // The maximum value is 10^6, so 2^20 is sufficient (approx 10^6).
        const int LIMIT = 1 << 20;
        vector<int> count_submask(LIMIT, 0);
        for (int x : nums) count_submask[x]++;

        // SOS DP (Sum Over Subsets)
        // After this, count_submask[mask] will store the number of elements in nums 
        // that are submasks of 'mask'.
        for (int i = 0; i < 20; ++i) {
            for (int mask = 0; mask < LIMIT; ++mask) {
                if (mask & (1 << i)) {
                    count_submask[mask] += count_submask[mask ^ (1 << i)];
                }
            }
        }

        long long MOD = 1e9 + 7;
        
        // Precompute powers of 2 modulo MOD
        vector<long long> pow2(n + 1);
        pow2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        long long K = 0;
        int total_set_bits = __builtin_popcount(total_or);

        // Inclusion-Exclusion Principle (PIE)
        // We want to count subsets B such that OR(B) == total_or.
        // Formula: Sum_{mask <= total_or} (-1)^(|total_or| - |mask|) * 2^(count of nums subset of mask)
        for (int mask = 0; mask < LIMIT; ++mask) {
            // We only care about masks that are submasks of total_or
            if ((mask & total_or) == mask) {
                long long ways = pow2[count_submask[mask]];
                int mask_set_bits = __builtin_popcount(mask);
                
                if ((total_set_bits - mask_set_bits) % 2 == 1) {
                    K = (K - ways + MOD) % MOD;
                } else {
                    K = (K + ways) % MOD;
                }
            }
        }

        // The answer is Total Subsequences - Subsets with OR equal to total_or
        long long total_subsequences = pow2[n];
        long long ans = (total_subsequences - K + MOD) % MOD;
        
        return ans;
    }
};
# @lc code=end