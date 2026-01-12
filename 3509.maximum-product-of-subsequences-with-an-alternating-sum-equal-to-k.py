#
# @lc app=leetcode id=3509 lang=python3
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        # dp[(sum, parity)] = max_product
        # parity 0: next element is at even index (added)
        # parity 1: next element is at odd index (subtracted)
        dp = {}

        for x in nums:
            new_dp = dp.copy()
            
            # Case: Start a new subsequence with x (x is at index 0, so it's even)
            if x <= limit:
                new_dp[(x, 1)] = max(new_dp.get((x, 1), -1), x)
            
            for (s, p), prod in dp.items():
                new_s = s + x if p == 0 else s - x
                new_prod = prod * x
                
                if new_prod <= limit:
                    new_p = 1 - p
                    new_dp[(new_s, new_p)] = max(new_dp.get((new_s, new_p), -1), new_prod)
            
            dp = new_dp
            
        ans = max(dp.get((k, 0), -1), dp.get((k, 1), -1))
        return ans
# @lc code=end