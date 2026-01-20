#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int countEffective(vector<int>& nums) {
        int n = nums.size();
        int S = 0;
        for (int x : nums) S |= x;
        
        if (S == 0) return 0;

        const int MOD = 1e9 + 7;
        
        // Find the number of bits needed to cover S
        int max_bits = 0;
        if (S > 0) {
            max_bits = 32 - __builtin_clz(S);
        }
        int W = 1 << max_bits;

        // freq[mask] will eventually store the number of elements in nums that are submasks of 'mask'
        vector<int> freq(W, 0);
        for (int x : nums) freq[x]++;

        // SOS DP (Sum Over Subsets)
        for (int i = 0; i < max_bits; ++i) {
            for (int mask = 0; mask < W; ++mask) {
                if (mask & (1 << i)) {
                    freq[mask] += freq[mask ^ (1 << i)];
                }
            }
        }

        // Precompute powers of 2
        vector<int> pow2(n + 1);
        pow2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pow2[i] = (pow2[i - 1] * 2LL) % MOD;
        }

        // Inclusion-Exclusion Principle
        // We want to find the number of subsets R such that OR(R) is a proper submask of S.
        // This is equivalent to finding the size of the union of sets A_k,
        // where A_k is the set of subsets R such that bit k is not set in OR(R).
        long long ans = 0;
        int s_pop = __builtin_popcount(S);

        // Iterate over all submasks t of S
        for (int t = S; ; t = (t - 1) & S) {
            if (t != S) {
                int k_pop = s_pop - __builtin_popcount(t);
                if (k_pop % 2 == 1) {
                    ans = (ans + pow2[freq[t]]) % MOD;
                } else {
                    ans = (ans - pow2[freq[t]] + MOD) % MOD;
                }
            }
            if (t == 0) break;
        }

        return (int)ans;
    }
};