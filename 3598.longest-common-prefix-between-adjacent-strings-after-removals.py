#
# @lc app=leetcode id=3598 lang=python3
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

from typing import List

# @lc code=start
class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        def compute_lcp(a: str, b: str) -> int:
            res = 0
            l = min(len(a), len(b))
            while res < l and a[res] == b[res]:
                res += 1
            return res
        
        n = len(words)
        if n < 2:
            return [0] * n
        
        m = n - 1
        L = [compute_lcp(words[k], words[k + 1]) for k in range(m)]
        
        left_max = [0] * (m + 1)
        for j in range(1, m + 1):
            left_max[j] = max(left_max[j - 1], L[j - 1])
        
        right_max = [0] * (m + 1)
        for j in range(m - 1, -1, -1):
            right_max[j] = max(right_max[j + 1], L[j])
        
        answer = [0] * n
        for i in range(n):
            if i == 0:
                answer[i] = right_max[1]
            elif i == n - 1:
                answer[i] = left_max[m - 1]
            else:
                rem_max = max(left_max[i - 1], right_max[i + 1])
                new_l = compute_lcp(words[i - 1], words[i + 1])
                answer[i] = max(rem_max, new_l)
        return answer
# @lc code=end
