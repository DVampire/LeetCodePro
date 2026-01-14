#
# @lc app=leetcode id=3458 lang=python3
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
class Solution:
    def maxSubstringLength(self, s: str, k: int) -> bool:
        n = len(s)
        
        if k == 0:
            return True
        
        # Find first and last occurrence of each character
        first = {}
        last = {}
        for i, c in enumerate(s):
            if c not in first:
                first[c] = i
            last[c] = i
        
        # Find all minimal special substrings
        intervals = set()
        
        for c in first:
            start = first[c]
            end = last[c]
            
            # Expand until closed
            i = start
            while i <= end:
                char = s[i]
                new_start = first[char]
                new_end = last[char]
                
                if new_start < start:
                    start = new_start
                    i = start
                else:
                    end = max(end, new_end)
                    i += 1
            
            # Check constraint: not the entire string
            if not (start == 0 and end == n - 1):
                intervals.add((start, end))
        
        # Sort by end point for greedy scheduling
        intervals = sorted(intervals, key=lambda x: x[1])
        
        # Greedy: select maximum non-overlapping intervals
        count = 0
        prev_end = -1
        for start, end in intervals:
            if start > prev_end:
                count += 1
                prev_end = end
        
        return count >= k
# @lc code=end