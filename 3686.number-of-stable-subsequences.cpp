#
# @lc app=leetcode id=3686 lang=cpp
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        long long dpE1 = 0; // Number of stable subsequences ending in exactly one even number
        long long dpE2 = 0; // Number of stable subsequences ending in exactly two even numbers
        long long dpO1 = 0; // Number of stable subsequences ending in exactly one odd number
        long long dpO2 = 0; // Number of stable subsequences ending in exactly two odd numbers
        const int MOD = 1000000007;

        for (int x : nums) {
            if (x % 2 == 0) {
                // Current element is even. It can follow an empty sequence, any odd-ending sequence,
                // or a single-even-ending sequence.
                long long wE1 = (1 + dpO1 + dpO2) % MOD;
                long long wE2 = dpE1;
                
                dpE1 = (dpE1 + wE1) % MOD;
                dpE2 = (dpE2 + wE2) % MOD;
            } else {
                // Current element is odd. It can follow an empty sequence, any even-ending sequence,
                // or a single-odd-ending sequence.
                long long wO1 = (1 + dpE1 + dpE2) % MOD;
                long long wO2 = dpO1;
                
                dpO1 = (dpO1 + wO1) % MOD;
                dpO2 = (dpO2 + wO2) % MOD;
            }
        }

        // The total number of stable subsequences is the sum of all tracked categories.
        return (int)((dpE1 + dpE2 + dpO1 + dpO2) % MOD);
    }
};
# @lc code=end