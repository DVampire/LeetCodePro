#
# @lc app=leetcode id=3762 lang=python3
#
# [3762] Minimum Operations to Equalize Subarrays
#
# @lc code=start
class Solution:
    def minOperations(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        result = []
        
        for l, r in queries:
            # Extract subarray
            subarray = nums[l:r+1]
            
            # Check if all elements have the same remainder modulo k
            remainder = subarray[0] % k
            if not all(x % k == remainder for x in subarray):
                result.append(-1)
                continue
            
            # Calculate quotients and sort them
            quotients = sorted([x // k for x in subarray])
            
            # Find median
            median = quotients[len(quotients) // 2]
            
            # Calculate total operations
            operations = sum(abs(q - median) for q in quotients)
            result.append(operations)
        
        return result
# @lc code=end