#
# @lc app=leetcode id=3458 lang=python3
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
class Solution:
    def maxSubstringLength(self, s: str, k: int) -> bool:
        n = len(s)
        
        # Count frequency of each character
        freq = {}
        for ch in s:
            freq[ch] = freq.get(ch, 0) + 1
        
        # Compute longest consecutive run for each character
        from collections import defaultdict
        longest_run = defaultdict(int)
        i = 0
        while i < n:
            ch = s[i]
            j = i
            while j < n and s[j] == ch:
                j += 1
            run_len = j - i
            longest_run[ch] = max(longest_run[ch], run_len)
            i = j
        
        eligible = 0
        for ch in freq:
            cnt = freq[ch]
            run_len = longest_run.get(ch)
            # Eligible if:
            #   All occurrences form a single consecutive block,
            #   The block is not the entire string.
            if cnt == run_len and cnt < n:
                eligible += 1
        
        return eligible >= k
# @lc code=end