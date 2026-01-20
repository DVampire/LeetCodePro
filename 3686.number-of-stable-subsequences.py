#
# @lc app=leetcode id=3686 lang=python3
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
class Solution:
    def countStableSubsequences(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        
        # dp[0]: count of stable subsequences ending with 1 even number
        # dp[1]: count of stable subsequences ending with 2 even numbers
        # dp[2]: count of stable subsequences ending with 1 odd number
        # dp[3]: count of stable subsequences ending with 2 odd numbers
        dp = [0] * 4
        
        for x in nums:
            if x % 2 == 0:
                # Current number is Even
                # Can form new subsequences ending in 2 evens by appending to those ending in 1 even
                added_to_1_even = dp[0]
                
                # Can form new subsequences ending in 1 even by appending to those ending in odds
                # Plus the single element subsequence [x]
                added_to_odds = (dp[2] + dp[3] + 1) % MOD
                
                dp[1] = (dp[1] + added_to_1_even) % MOD
                dp[0] = (dp[0] + added_to_odds) % MOD
            else:
                # Current number is Odd
                # Can form new subsequences ending in 2 odds by appending to those ending in 1 odd
                added_to_1_odd = dp[2]
                
                # Can form new subsequences ending in 1 odd by appending to those ending in evens
                # Plus the single element subsequence [x]
                added_to_evens = (dp[0] + dp[1] + 1) % MOD
                
                dp[3] = (dp[3] + added_to_1_odd) % MOD
                dp[2] = (dp[2] + added_to_evens) % MOD
                
        return sum(dp) % MOD
# @lc code=end