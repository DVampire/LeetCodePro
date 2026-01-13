#
# @lc app=leetcode id=3525 lang=python3
#
# [3525] Find X Value of Array II
#

# @lc code=start
class Solution:
    def resultArray(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        result = []
        
        for index, value, start, x in queries:
            # Update nums[index] to value (persists for future queries)
            nums[index] = value
            
            # Get the subarray starting from start
            arr = nums[start:]
            
            # Count how many ways to remove suffix such that product % k == x
            count = 0
            product = 1
            
            # Try all possible lengths (removing different suffixes)
            for i in range(len(arr)):
                product = (product * arr[i]) % k
                if product == x:
                    count += 1
            
            result.append(count)
        
        return result
# @lc code=end