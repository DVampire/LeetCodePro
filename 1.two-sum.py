#
# @lc app=leetcode id=1 lang=python3
#
# [1] Two Sum
#

# @lc code=start
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        # Create a dictionary to store value: index mapping
        prevMap = {}
        
        for i, n in enumerate(nums):
            # Calculate the value needed to reach the target
            diff = target - n
            # If the complement exists in the map, return the pair of indices
            if diff in prevMap:
                return [prevMap[diff], i]
            # Otherwise, store the current number and its index
            prevMap[n] = i
        
        # The problem guarantees exactly one solution, so we don't need a fallback
        return []
# @lc code=end