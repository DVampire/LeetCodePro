#
# @lc app=leetcode id=3743 lang=python3
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        
        def max_score_linear(arr, k):
            m = len(arr)
            dp = [[float('-inf')] * (k + 1) for _ in range(m + 1)]
            dp[0][0] = 0
            
            for i in range(1, m + 1):
                for j in range(1, min(i, k) + 1):
                    for l in range(j - 1, i):
                        if dp[l][j-1] != float('-inf'):
                            subarr = arr[l:i]
                            range_val = max(subarr) - min(subarr)
                            dp[i][j] = max(dp[i][j], dp[l][j-1] + range_val)
            
            result = 0
            for j in range(1, k + 1):
                if dp[m][j] != float('-inf'):
                    result = max(result, dp[m][j])
            return result
        
        max_score = 0
        for start in range(n):
            arr = nums[start:] + nums[:start]
            score = max_score_linear(arr, k)
            max_score = max(max_score, score)
        
        return max_score
# @lc code=end