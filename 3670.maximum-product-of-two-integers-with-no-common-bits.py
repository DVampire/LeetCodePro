#
# @lc app=leetcode id=3670 lang=python3
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        # The maximum value in nums is 10^6, which is less than 2^20 (1,048,576).
        # We need 20 bits to represent all numbers.
        NUM_BITS = 20
        MAX_MASK = 1 << NUM_BITS
        
        # dp[mask] will store the maximum number in 'nums' that is a submask of 'mask'.
        # Initialize with 0.
        dp = [0] * MAX_MASK
        
        # Fill dp with the numbers present in the input.
        # If a number x is present, it is a submask of itself.
        for num in nums:
            dp[num] = max(dp[num], num)
            
        # Propagate the maximum values using SOS DP (Sum Over Subsets).
        # For each bit position 'i', and each 'mask', if the 'i-th' bit is set in 'mask',
        # then any submask of 'mask ^ (1 << i)' is also a submask of 'mask'.
        # We want dp[mask] to be the max value among all submasks.
        for i in range(NUM_BITS):
            bit = 1 << i
            for mask in range(MAX_MASK):
                if mask & bit:
                    # If the i-th bit is set, we can either keep it or turn it off.
                    # Turning it off gives us the submask 'mask ^ bit'.
                    # We take the max of the current value and the value from the submask.
                    if dp[mask ^ bit] > dp[mask]:
                        dp[mask] = dp[mask ^ bit]
                        
        max_prod = 0
        full_mask = MAX_MASK - 1
        
        # Iterate through each number to find its best disjoint pair.
        for num in nums:
            # The complement contains all bits NOT set in num.
            # Any number that is disjoint from 'num' must be a submask of 'complement'.
            complement = full_mask ^ num
            
            # dp[complement] gives the largest number from the array that fits into the complement mask.
            partner = dp[complement]
            
            # If partner is 0, it means no valid disjoint number was found (or only 0, which gives product 0).
            current_prod = num * partner
            if current_prod > max_prod:
                max_prod = current_prod
                
        return max_prod

# @lc code=end