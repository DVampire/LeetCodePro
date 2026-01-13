#
# @lc app=leetcode id=3513 lang=python3
#
# [3513] Number of Unique XOR Triplets I
#
# @lc code=start
class Solution:
    def uniqueXorTriplets(self, nums: List[int]) -> int:
        n = len(nums)
        xor_values = set()
        
        for i in range(n):
            for j in range(i, n):
                for k in range(j, n):
                    xor_val = nums[i] ^ nums[j] ^ nums[k]
                    xor_values.add(xor_val)
        
        return len(xor_values)
# @lc code=end