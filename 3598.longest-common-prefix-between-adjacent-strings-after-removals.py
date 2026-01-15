#
# @lc app=leetcode id=3598 lang=python3
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

# @lc code=start
class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        n = len(words)
        if n <= 2:
            return [0] * n
        
        def compute_lcp(s1, s2):
            length = min(len(s1), len(s2))
            for k in range(length):
                if s1[k] != s2[k]:
                    return k
            return length
        
        # Compute LCP for all adjacent pairs
        lcp = [compute_lcp(words[j], words[j + 1]) for j in range(n - 1)]
        
        # Compute prefix max: prefix_max[j] = max(lcp[0], ..., lcp[j])
        prefix_max = [0] * (n - 1)
        prefix_max[0] = lcp[0]
        for j in range(1, n - 1):
            prefix_max[j] = max(prefix_max[j - 1], lcp[j])
        
        # Compute suffix max: suffix_max[j] = max(lcp[j], ..., lcp[n-2])
        suffix_max = [0] * (n - 1)
        suffix_max[n - 2] = lcp[n - 2]
        for j in range(n - 3, -1, -1):
            suffix_max[j] = max(suffix_max[j + 1], lcp[j])
        
        answer = [0] * n
        
        # Remove index 0: remaining LCPs are lcp[1], ..., lcp[n-2]
        answer[0] = suffix_max[1]
        
        # Remove index n-1: remaining LCPs are lcp[0], ..., lcp[n-3]
        answer[n - 1] = prefix_max[n - 3]
        
        # Remove index i (0 < i < n-1)
        for i in range(1, n - 1):
            # New pair formed: (i-1, i+1)
            max_val = compute_lcp(words[i - 1], words[i + 1])
            
            # Pairs before: lcp[0], ..., lcp[i-2]
            if i >= 2:
                max_val = max(max_val, prefix_max[i - 2])
            
            # Pairs after: lcp[i+1], ..., lcp[n-2]
            if i <= n - 3:
                max_val = max(max_val, suffix_max[i + 1])
            
            answer[i] = max_val
        
        return answer
# @lc code=end