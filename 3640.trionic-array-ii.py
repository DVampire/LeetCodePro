#
# @lc app=leetcode id=3640 lang=python3
#
# [3640] Trionic Array II
#
# @lc code=start
class Solution:
    def maxSumTrionic(self, nums: List[int]) -> int:
        n = len(nums)
        
        inc1_sum = [0] * n
        inc1_len = [0] * n
        dec_sum = [float('-inf')] * n
        dec_len = [0] * n
        inc2_sum = [float('-inf')] * n
        
        inc1_sum[0] = nums[0]
        inc1_len[0] = 1
        
        for i in range(1, n):
            # Update inc1: strictly increasing phase
            if nums[i] > nums[i-1]:
                inc1_sum[i] = inc1_sum[i-1] + nums[i]
                inc1_len[i] = inc1_len[i-1] + 1
            else:
                inc1_sum[i] = nums[i]
                inc1_len[i] = 1
            
            # Update dec: inc + dec phases
            dec_sum[i] = float('-inf')
            dec_len[i] = 0
            if nums[i] < nums[i-1]:
                # Transition from inc1[i-1] if it has at least 2 elements
                if inc1_len[i-1] >= 2:
                    dec_sum[i] = inc1_sum[i-1] + nums[i]
                    dec_len[i] = 2
                # Extend from dec[i-1]
                if dec_sum[i-1] != float('-inf'):
                    new_sum = dec_sum[i-1] + nums[i]
                    if new_sum > dec_sum[i]:
                        dec_sum[i] = new_sum
                        dec_len[i] = dec_len[i-1] + 1
            
            # Update inc2: inc + dec + inc phases
            inc2_sum[i] = float('-inf')
            if nums[i] > nums[i-1]:
                # Transition from dec[i-1] if dec phase has at least 2 elements
                if dec_sum[i-1] != float('-inf') and dec_len[i-1] >= 2:
                    inc2_sum[i] = dec_sum[i-1] + nums[i]
                # Extend from inc2[i-1]
                if inc2_sum[i-1] != float('-inf'):
                    inc2_sum[i] = max(inc2_sum[i], inc2_sum[i-1] + nums[i])
        
        return max(inc2_sum)
# @lc code=end