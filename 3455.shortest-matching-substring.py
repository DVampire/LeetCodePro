#
# @lc app=leetcode id=3455 lang=python3
#
# [3455] Shortest Matching Substring
#

# @lc code=start
import bisect

class Solution:
    def shortestMatchingSubstring(self, s: str, p: str) -> int:
        def find_all(text, pattern):
            if not pattern:
                return list(range(len(text) + 1))
            
            m = len(pattern)
            n = len(text)
            pi = [0] * m
            j = 0
            for i in range(1, m):
                while j > 0 and pattern[i] != pattern[j]:
                    j = pi[j-1]
                if pattern[i] == pattern[j]:
                    j += 1
                pi[i] = j
            
            res = []
            j = 0
            for i in range(n):
                while j > 0 and text[i] != pattern[j]:
                    j = pi[j-1]
                if text[i] == pattern[j]:
                    j += 1
                if j == m:
                    res.append(i - m + 1)
                    j = pi[j-1]
            return res

        parts = p.split('*')
        p1, p2, p3 = parts[0], parts[1], parts[2]
        
        pos1 = find_all(s, p1)
        pos2 = find_all(s, p2)
        pos3 = find_all(s, p3)
        
        if not pos1 or not pos2 or not pos3:
            return -1
        
        ans = float('inf')
        len1, len2, len3 = len(p1), len(p2), len(p3)
        
        for s2 in pos2:
            # Find largest s1 in pos1 such that s1 <= s2 - len1
            idx1 = bisect.bisect_right(pos1, s2 - len1)
            if idx1 == 0:
                continue
            s1 = pos1[idx1 - 1]
            
            # Find smallest s3 in pos3 such that s3 >= s2 + len2
            idx3 = bisect.bisect_left(pos3, s2 + len2)
            if idx3 == len(pos3):
                continue
            s3 = pos3[idx3]
            
            ans = min(ans, (s3 + len3) - s1)
            
        return int(ans) if ans != float('inf') else -1
# @lc code=end