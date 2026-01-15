#
# @lc app=leetcode id=3748 lang=python3
#
# [3748] Count Stable Subarrays
#

# @lc code=start
class Solution:
    def countStableSubarrays(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        
        # Build segments of non-decreasing subarrays
        seg = [0] * n  # seg[i] = segment index containing position i
        seg_start = [0]  # Start index of each segment
        seg_end = []     # End index of each segment
        
        current_seg = 0
        for i in range(n - 1):
            seg[i] = current_seg
            if nums[i] > nums[i + 1]:  # Breaking point
                seg_end.append(i)
                current_seg += 1
                seg_start.append(i + 1)
        seg[n - 1] = current_seg
        seg_end.append(n - 1)
        
        num_segments = len(seg_start)
        
        # Count of subarrays in a range of length `length`
        def count_subarrays(length):
            return length * (length + 1) // 2
        
        # Prefix sum of full segment counts
        prefix_count = [0] * (num_segments + 1)
        for j in range(num_segments):
            length = seg_end[j] - seg_start[j] + 1
            prefix_count[j + 1] = prefix_count[j] + count_subarrays(length)
        
        ans = []
        for l, r in queries:
            seg_l = seg[l]
            seg_r = seg[r]
            
            if seg_l == seg_r:
                # Query range is within a single segment
                ans.append(count_subarrays(r - l + 1))
            else:
                # First partial segment
                first_partial = count_subarrays(seg_end[seg_l] - l + 1)
                # Last partial segment
                last_partial = count_subarrays(r - seg_start[seg_r] + 1)
                # Full segments in between
                full_count = prefix_count[seg_r] - prefix_count[seg_l + 1]
                ans.append(first_partial + last_partial + full_count)
        
        return ans
# @lc code=end