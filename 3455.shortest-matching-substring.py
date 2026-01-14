#
# @lc app=leetcode id=3455 lang=python3
#
# [3455] Shortest Matching Substring
#

# @lc code=start
import bisect

class Solution:
    def shortestMatchingSubstring(self, s: str, p: str) -> int:
        parts = p.split('*')
        A, B, C = parts[0], parts[1], parts[2]
        
        n = len(s)
        
        if len(A) == 0 and len(B) == 0 and len(C) == 0:
            return 0
        
        def find_all(pattern):
            if len(pattern) == 0:
                return None
            positions = []
            m = len(pattern)
            lps = [0] * m
            length = 0
            i = 1
            while i < m:
                if pattern[i] == pattern[length]:
                    length += 1
                    lps[i] = length
                    i += 1
                else:
                    if length != 0:
                        length = lps[length - 1]
                    else:
                        lps[i] = 0
                        i += 1
            i = 0
            j = 0
            while i < n:
                if pattern[j] == s[i]:
                    i += 1
                    j += 1
                if j == m:
                    positions.append(i - j)
                    j = lps[j - 1]
                elif i < n and pattern[j] != s[i]:
                    if j != 0:
                        j = lps[j - 1]
                    else:
                        i += 1
            return positions
        
        A_pos = find_all(A)
        B_pos = find_all(B)
        C_pos = find_all(C)
        
        min_len = float('inf')
        
        if B_pos is None:
            if A_pos is None and C_pos is None:
                return 0
            elif A_pos is None:
                if not C_pos:
                    return -1
                return len(C)
            elif C_pos is None:
                if not A_pos:
                    return -1
                return len(A)
            else:
                if not A_pos or not C_pos:
                    return -1
                j = 0
                for a in A_pos:
                    while j < len(C_pos) and C_pos[j] < a + len(A):
                        j += 1
                    if j < len(C_pos):
                        c = C_pos[j]
                        min_len = min(min_len, c + len(C) - a)
                return min_len if min_len != float('inf') else -1
        
        if not B_pos:
            return -1
        
        for b in B_pos:
            if A_pos is None:
                a = b
            else:
                target = b - len(A)
                if target < 0:
                    continue
                idx = bisect.bisect_right(A_pos, target)
                if idx == 0:
                    continue
                a = A_pos[idx - 1]
            
            if C_pos is None:
                c = b + len(B)
            else:
                target = b + len(B)
                idx = bisect.bisect_left(C_pos, target)
                if idx == len(C_pos):
                    continue
                c = C_pos[idx]
            
            length = c + len(C) - a
            min_len = min(min_len, length)
        
        return min_len if min_len != float('inf') else -1
# @lc code=end