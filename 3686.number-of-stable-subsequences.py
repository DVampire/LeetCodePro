#
# @lc app=leetcode id=3686 lang=python3
#
# [3686] Number of Stable Subsequences
#
# @lc code=start
class Solution:
    def countStableSubsequences(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        
        # States: [EMPTY, E1, E2, O1, O2]
        # EMPTY: empty subsequence
        # E1: ends with 1 even number
        # E2: ends with 2 consecutive even numbers
        # O1: ends with 1 odd number
        # O2: ends with 2 consecutive odd numbers
        dp = [1, 0, 0, 0, 0]
        
        for num in nums:
            new_dp = dp[:]  # All subsequences that skip current element
            parity = num % 2
            
            if parity == 0:  # even number
                # Can transition from EMPTY, O1, O2 to E1
                new_dp[1] = (new_dp[1] + dp[0] + dp[3] + dp[4]) % MOD
                # Can transition from E1 to E2
                new_dp[2] = (new_dp[2] + dp[1]) % MOD
            else:  # odd number
                # Can transition from EMPTY, E1, E2 to O1
                new_dp[3] = (new_dp[3] + dp[0] + dp[1] + dp[2]) % MOD
                # Can transition from O1 to O2
                new_dp[4] = (new_dp[4] + dp[3]) % MOD
            
            dp = new_dp
        
        # Sum all non-empty stable subsequences
        return sum(dp[1:]) % MOD
# @lc code=end