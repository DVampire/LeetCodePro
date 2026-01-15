#
# @lc app=leetcode id=3768 lang=python3
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
class Solution:
    def minInversionCount(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if k == 1:
            return 0
        
        # Coordinate compression
        sorted_nums = sorted(set(nums))
        rank = {v: i + 1 for i, v in enumerate(sorted_nums)}
        max_rank = len(sorted_nums)
        
        # BIT for counting
        bit = [0] * (max_rank + 1)
        
        def update(i, delta=1):
            while i <= max_rank:
                bit[i] += delta
                i += i & (-i)
        
        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & (-i)
            return s
        
        # Count inversions in first window
        inv_count = 0
        for i in range(k):
            r = rank[nums[i]]
            # Count elements > nums[i] already added
            inv_count += query(max_rank) - query(r)
            update(r)
        
        min_inv = inv_count
        
        # Slide the window
        for i in range(n - k):
            # Remove nums[i] from window
            r_old = rank[nums[i]]
            update(r_old, -1)
            removed_inv = query(r_old - 1)  # Elements < nums[i] remaining in window
            
            # Add nums[i+k] to window
            r_new = rank[nums[i + k]]
            added_inv = query(max_rank) - query(r_new)  # Elements > nums[i+k] in window
            update(r_new)
            
            inv_count = inv_count - removed_inv + added_inv
            min_inv = min(min_inv, inv_count)
        
        return min_inv
# @lc code=end