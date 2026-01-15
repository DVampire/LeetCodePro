#
# @lc app=leetcode id=3640 lang=python3
#
# [3640] Trionic Array II
#

# @lc code=start
class Solution:
    def maxSumTrionic(self, nums: List[int]) -> int:
        n = len(nums)
        NEG_INF = float('-inf')
        
        # DP states:
        # A_1: first increasing phase with exactly 1 element
        # A_2: first increasing phase with >= 2 elements
        # B: first increasing done, in decreasing phase (>= 2 elements)
        # C: complete trionic (all three phases have >= 2 elements)
        
        A_1 = nums[0]
        A_2 = NEG_INF
        B = NEG_INF
        C = NEG_INF
        
        result = NEG_INF
        
        for i in range(1, n):
            new_A_1 = nums[i]
            new_A_2 = NEG_INF
            new_B = NEG_INF
            new_C = NEG_INF
            
            if nums[i] > nums[i-1]:  # strictly increasing
                # Extend first increasing
                new_A_2 = max(A_1 + nums[i], A_2 + nums[i])
                # Extend second increasing (transition from B or extend C)
                new_C = max(B + nums[i], C + nums[i])
            elif nums[i] < nums[i-1]:  # strictly decreasing
                # Start or extend decreasing (transition from A_2 or extend B)
                new_B = max(A_2 + nums[i], B + nums[i])
            
            A_1, A_2, B, C = new_A_1, new_A_2, new_B, new_C
            result = max(result, C)
        
        return result
# @lc code=end