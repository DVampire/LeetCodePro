#
# @lc app=leetcode id=3640 lang=python3
#
# [3640] Trionic Array II
#

# @lc code=start
class Solution:
    def maxSumTrionic(self, nums: List[int]) -> int:
        n = len(nums)
        # inc1: max sum of the first increasing segment ending at current index
        # dec: max sum of (inc1 + decreasing segment) ending at current index
        # inc2: max sum of (inc1 + dec + increasing segment) ending at current index
        
        # Initialize with a very small number representing infinity
        inf = float('inf')
        inc1 = -inf
        dec = -inf
        inc2 = -inf
        
        ans = -inf
        
        for i in range(1, n):
            curr = nums[i]
            prev = nums[i-1]
            
            # Calculate new states based on transition from prev to curr
            # We use temporary variables for the next state to avoid using updated values within the same step
            if curr > prev:
                # Increasing step
                
                # update inc2: can extend previous inc2 OR start inc2 from a previous dec
                # Since we are going UP, we can be in the second increasing phase
                new_inc2 = -inf
                if inc2 != -inf:
                    new_inc2 = max(new_inc2, inc2 + curr)
                if dec != -inf:
                    new_inc2 = max(new_inc2, dec + curr)
                
                # update inc1: can extend previous inc1 OR start new inc1 with (prev, curr)
                new_inc1 = prev + curr
                if inc1 != -inf:
                    new_inc1 = max(new_inc1, inc1 + curr)
                
                # Cannot be in decreasing phase if we just went up
                new_dec = -inf
                
                inc1, dec, inc2 = new_inc1, new_dec, new_inc2
                
            elif curr < prev:
                # Decreasing step
                
                # update dec: can extend previous dec OR start dec from a previous inc1
                # Since we are going DOWN, we can be in the middle decreasing phase
                new_dec = -inf
                if dec != -inf:
                    new_dec = max(new_dec, dec + curr)
                if inc1 != -inf:
                    new_dec = max(new_dec, inc1 + curr)
                
                # Cannot extend increasing phases if we just went down
                new_inc1 = -inf
                new_inc2 = -inf
                
                inc1, dec, inc2 = new_inc1, new_dec, new_inc2
                
            else:
                # Equal elements: strictly increasing/decreasing property broken
                inc1, dec, inc2 = -inf, -inf, -inf
            
            if inc2 != -inf:
                ans = max(ans, inc2)
                
        return ans
# @lc code=end