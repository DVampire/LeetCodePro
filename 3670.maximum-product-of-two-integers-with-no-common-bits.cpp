#
# @lc app=leetcode id=3670 lang=cpp
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        // The maximum value is 10^6, which is less than 2^20 (1,048,576).
        // We can use SOS DP (Sum Over Subsets) to find the maximum number
        // that is a submask of any given mask.
        
        const int MAX_BITS = 20;
        const int RANGE = 1 << MAX_BITS;
        
        // dp[mask] stores the maximum number present in nums that is a submask of 'mask'.
        vector<int> dp(RANGE, 0);
        
        for (int num : nums) {
            dp[num] = num;
        }
        
        // SOS DP propagation
        // We iterate through each bit position.
        // If a mask has the i-th bit set, it can cover submasks that don't have the i-th bit set.
        for (int i = 0; i < MAX_BITS; ++i) {
            for (int mask = 0; mask < RANGE; ++mask) {
                if (mask & (1 << i)) {
                    dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
                }
            }
        }
        
        long long maxProd = 0;
        int fullMask = RANGE - 1;
        
        for (int num : nums) {
            // We need a number 'y' such that (num & y) == 0.
            // This implies 'y' must be a submask of the complement of 'num'.
            // The complement mask relative to 20 bits is (fullMask ^ num).
            int complement = fullMask ^ num;
            
            // dp[complement] gives the largest number in nums that is a submask of complement.
            // This number shares no bits with 'num'.
            if (dp[complement] > 0) {
                maxProd = max(maxProd, (long long)num * dp[complement]);
            }
        }
        
        return maxProd;
    }
};
# @lc code=end