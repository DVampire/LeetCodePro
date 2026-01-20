#
# @lc app=leetcode id=3598 lang=python3
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

# @lc code=start
class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        n = len(words)
        if n <= 1:
            return [0] * n
        
        # Helper to compute LCP of two strings
        def get_lcp(s1, s2):
            length = min(len(s1), len(s2))
            for i in range(length):
                if s1[i] != s2[i]:
                    return i
            return length

        # Precompute LCP of adjacent pairs in the original array
        # adj_lcp[i] stores lcp(words[i], words[i+1])
        adj_lcp = []
        for i in range(n - 1):
            adj_lcp.append(get_lcp(words[i], words[i+1]))
            
        # Precompute prefix maximums of adj_lcp
        # prefix_max[i] = max(adj_lcp[0], ..., adj_lcp[i])
        prefix_max = [0] * (n - 1)
        current_max = 0
        for i in range(n - 1):
            current_max = max(current_max, adj_lcp[i])
            prefix_max[i] = current_max
            
        # Precompute suffix maximums of adj_lcp
        # suffix_max[i] = max(adj_lcp[i], ..., adj_lcp[n-2])
        suffix_max = [0] * (n - 1)
        current_max = 0
        for i in range(n - 2, -1, -1):
            current_max = max(current_max, adj_lcp[i])
            suffix_max[i] = current_max
            
        ans = []
        for i in range(n):
            val = 0
            
            # 1. Max LCP from pairs completely to the left of the removed index i
            # These are pairs (words[0], words[1]) ... (words[i-2], words[i-1])
            # The last index in adj_lcp we can use is i-2.
            if i >= 2:
                val = max(val, prefix_max[i-2])
            
            # 2. Max LCP from pairs completely to the right of the removed index i
            # These are pairs (words[i+1], words[i+2]) ... (words[n-2], words[n-1])
            # The first index in adj_lcp we can use is i+1.
            if i <= n - 2:
                val = max(val, suffix_max[i+1])
                
            # 3. The new adjacent pair formed by removing words[i]
            # This is (words[i-1], words[i+1])
            if i > 0 and i < n - 1:
                val = max(val, get_lcp(words[i-1], words[i+1]))
                
            ans.append(val)
            
        return ans
# @lc code=end