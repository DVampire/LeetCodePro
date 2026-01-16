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
        
        # Precompute character frequencies in the entire string
        total_count = [0] * 26
        for char in s:
            total_count[ord(char) - ord('a')] += 1
        
        # Find all special substrings
        special_intervals = []
        
        # For each possible substring
        for i in range(n):
            # Character count in current substring
            substring_count = [0] * 26
            for j in range(i, n):
                # Add current character to substring count
                substring_count[ord(s[j]) - ord('a')] += 1
                
                # Check if this substring is special
                # A substring is special if every character in it appears only within this substring
                is_special = True
                for c in range(26):
                    # If character appears in substring but also appears outside
                    if substring_count[c] > 0 and substring_count[c] != total_count[c]:
                        is_special = False
                        break
                
                # Also, substring cannot be the entire string
                if is_special and (j - i + 1) < n:
                    special_intervals.append((i, j))
        
        # Now we need to find maximum number of disjoint intervals we can select
        if not special_intervals:
            return k == 0
        
        # Sort intervals by end position for greedy selection
        special_intervals.sort(key=lambda x: x[1])
        
        # Greedily select disjoint intervals
        count = 0
        last_end = -1
        
        for start, end in special_intervals:
            if start > last_end:  # No overlap
                count += 1
                last_end = end
                if count >= k:
                    return True
        
        return count >= k
# @lc code=end