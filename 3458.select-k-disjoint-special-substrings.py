#
# @lc app=leetcode id=3458 lang=python3
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
class Solution:
    def maxSubstringLength(self, s: str, k: int) -> bool:
        if k == 0:
            return True
        
        n = len(s)
        first = {}
        last = {}
        
        # Precompute the first and last occurrence of each character
        for i, char in enumerate(s):
            if char not in first:
                first[char] = i
            last[char] = i
        
        intervals = []
        # For each character, find the minimal special substring starting at its first occurrence
        for char in first:
            L = first[char]
            R = last[char]
            
            i = L
            possible = True
            while i <= R:
                char_at_i = s[i]
                # If any character in the current range starts before our start index L,
                # then no special substring can start at L.
                if first[char_at_i] < L:
                    possible = False
                    break
                # Expand the range to include all occurrences of the current character
                if last[char_at_i] > R:
                    R = last[char_at_i]
                i += 1
            
            if possible:
                # A special substring cannot be the entire string
                if not (L == 0 and R == n - 1):
                    intervals.append((L, R))
        
        # Greedy approach to find the maximum number of disjoint intervals
        # Sort intervals by their end positions
        intervals.sort(key=lambda x: x[1])
        
        count = 0
        last_end = -1
        for start, end in intervals:
            if start > last_end:
                count += 1
                last_end = end
        
        return count >= k
# @lc code=end