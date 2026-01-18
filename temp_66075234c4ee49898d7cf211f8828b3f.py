#
# @lc app=leetcode id=3356 lang=python3
#
# [3356] Zero Array Transformation II
#

# @lc code=start
class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        
        def check(k):
            # Use a difference array to efficiently calculate the total decrement 
            # possible at each index using the first k queries.
            diff = [0] * (n + 1)
            for i in range(k):
                l, r, v = queries[i]
                diff[l] += v
                diff[r + 1] -= v
            
            # Calculate the prefix sum of the difference array to get the actual 
            # capacity to decrement each index.
            curr = 0
            for i in range(n):
                curr += diff[i]
                # If the total possible decrement is less than the required amount 
                # to make nums[i] zero, then k queries are insufficient.
                if curr < nums[i]:
                    return False
            return True
        
        # Binary search for the minimum k in the range [0, len(queries)].
        # This is possible because the problem is monotonic: if k queries 
        # work, then k+1 queries also work.
        low, high = 0, len(queries)
        ans = -1
        
        while low <= high:
            mid = (low + high) // 2
            if check(mid):
                ans = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return ans
# @lc code=end