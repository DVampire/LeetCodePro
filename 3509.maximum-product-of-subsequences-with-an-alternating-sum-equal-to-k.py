#
# @lc app=leetcode id=3509 lang=python3
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
from typing import List

class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        # dp[(alt_sum, parity)] = set of achievable products
        # parity: 0 = even length, 1 = odd length
        dp = {}
        
        for num in nums:
            new_dp = {}
            
            # Copy existing states (option: skip current num)
            for key, prods in dp.items():
                new_dp[key] = prods.copy()
            
            # Option: Start a new subsequence with this number
            if num <= limit:
                key = (num, 1)  # alt_sum = num, odd length (length 1)
                if key not in new_dp:
                    new_dp[key] = set()
                new_dp[key].add(num)
            
            # Option: Extend existing subsequences
            for (alt, parity), prods in dp.items():
                if parity == 1:  # odd length -> next position is odd (sign -)
                    new_alt = alt - num
                    new_parity = 0
                else:  # even length -> next position is even (sign +)
                    new_alt = alt + num
                    new_parity = 1
                
                for prod in prods:
                    new_prod = prod * num
                    if new_prod <= limit:
                        key = (new_alt, new_parity)
                        if key not in new_dp:
                            new_dp[key] = set()
                        new_dp[key].add(new_prod)
            
            dp = new_dp
        
        # Find the maximum product with alternating sum = k
        result = -1
        for parity in [0, 1]:
            if (k, parity) in dp:
                result = max(result, max(dp[(k, parity)]))
        
        return result
# @lc code=end