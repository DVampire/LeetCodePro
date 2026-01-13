#
# @lc app=leetcode id=3509 lang=python3
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        # dp[(sum, length_mod_2, is_empty)] = max_product
        # sum: current alternating sum
        # length_mod_2: 0 for even length, 1 for odd length
        # is_empty: True if subsequence is empty, False otherwise
        dp = {(0, 0, True): 1}  # Start with empty subsequence
        
        for num in nums:
            new_dp = {}
            
            # Option 1: Don't take current number
            for state, prod in dp.items():
                if state not in new_dp or new_dp[state] < prod:
                    new_dp[state] = prod
            
            # Option 2: Take current number
            for (curr_sum, length_mod_2, is_empty), prod in dp.items():
                if length_mod_2 == 0:  # Even length, add number
                    new_sum = curr_sum + num
                    new_length_mod_2 = 1
                else:  # Odd length, subtract number
                    new_sum = curr_sum - num
                    new_length_mod_2 = 0
                
                new_prod = prod * num
                if new_prod <= limit:
                    new_state = (new_sum, new_length_mod_2, False)
                    if new_state not in new_dp or new_dp[new_state] < new_prod:
                        new_dp[new_state] = new_prod
            
            dp = new_dp
        
        # Find maximum product with sum = k and non-empty subsequence
        result = -1
        for (curr_sum, length_mod_2, is_empty), prod in dp.items():
            if curr_sum == k and not is_empty:
                result = max(result, prod)
        
        return result
# @lc code=end