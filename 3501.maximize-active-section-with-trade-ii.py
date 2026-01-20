#
# @lc app=leetcode id=3501 lang=python3
#
# [3501] Maximize Active Section with Trade II
#

from typing import List
import bisect

# @lc code=start
class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + (1 if s[i] == '1' else 0)
        
        islands = []
        i = 0
        while i < n:
            if s[i] == '1':
                start = i
                while i < n and s[i] == '1':
                    i += 1
                end = i - 1
                # full left 0s
                fl = 0
                pos = start - 1
                while pos >= 0 and s[pos] == '0':
                    fl += 1
                    pos -= 1
                # full right 0s
                fr = 0
                pos = end + 1
                while pos < n and s[pos] == '0':
                    fr += 1
                    pos += 1
                islands.append((start, end, fl, fr))
            else:
                i += 1
        
        m = len(islands)
        if m == 0:
            return [prefix[ri + 1] - prefix[li] for li, ri in queries]
        
        starts = [island[0] for island in islands]
        ends = [island[1] for island in islands]
        
        answer = []
        for li, ri in queries:
            orig = prefix[ri + 1] - prefix[li]
            if ri - li < 2:
                answer.append(orig)
                continue
            
            # first j: starts[j] >= li+1
            j = bisect.bisect_left(starts, li + 1)
            # last k: ends[k] <= ri-1
            k = bisect.bisect_right(ends, ri - 1) - 1
            
            if j > k:
                answer.append(orig)
                continue
            
            maxp = 0
            for ii in range(j, k + 1):
                st, en, fl, fr = islands[ii]
                dl = st - li
                dr = ri - en
                p = min(fl, dl) + min(fr, dr)
                if p > maxp:
                    maxp = p
            answer.append(orig + maxp)
        return answer
# @lc code=end