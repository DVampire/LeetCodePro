#
# @lc app=leetcode id=3455 lang=python3
#
# [3455] Shortest Matching Substring
#

# @lc code=start
import bisect

class Solution:
    def shortestMatchingSubstring(self, s: str, p: str) -> int:
        def find_matches(text: str, pat: str) -> list[int]:
            n, m = len(text), len(pat)
            if m == 0 or m > n:
                return []
            # KMP prefix function
            pi = [0] * m
            j = 0
            for i in range(1, m):
                while j > 0 and pat[i] != pat[j]:
                    j = pi[j - 1]
                if pat[i] == pat[j]:
                    j += 1
                pi[i] = j
            # Search
            matches = []
            j = 0
            for i in range(n):
                while j > 0 and text[i] != pat[j]:
                    j = pi[j - 1]
                if text[i] == pat[j]:
                    j += 1
                if j == m:
                    matches.append(i - m + 1)
                    j = pi[j - 1]
            return matches

        star1 = p.find('*')
        star2 = p.find('*', star1 + 1)
        A = p[:star1]
        B = p[star1 + 1:star2]
        C = p[star2 + 1:]
        lenA, lenB, lenC = len(A), len(B), len(C)
        n = len(s)
        if lenA == 0 and lenB == 0 and lenC == 0:
            return 0

        startsA = find_matches(s, A) if lenA > 0 else []
        startsB = find_matches(s, B)
        startsC = find_matches(s, C) if lenC > 0 else []

        min_len = float('inf')

        if lenB > 0:
            for kb in startsB:
                target_jc = kb + lenB
                if lenC == 0:
                    jc_next = target_jc
                else:
                    idx = bisect.bisect_left(startsC, target_jc)
                    if idx == len(startsC):
                        continue
                    jc_next = startsC[idx]
                j = jc_next + lenC - 1
                target_ia = kb - lenA
                if target_ia < 0:
                    continue
                if lenA == 0:
                    i_start = target_ia
                else:
                    idx = bisect.bisect_right(startsA, target_ia) - 1
                    if idx < 0:
                        continue
                    i_start = startsA[idx]
                if i_start > j:
                    continue
                length = j - i_start + 1
                if length < min_len:
                    min_len = length
        else:
            # lenB == 0
            startsA = find_matches(s, A) if lenA > 0 else []
            startsC = find_matches(s, C) if lenC > 0 else []
            if lenC == 0:
                if lenA == 0:
                    min_len = 0
                elif startsA:
                    min_len = lenA
            else:
                for jc in startsC:
                    target_ia = jc - lenA
                    if target_ia < 0:
                        continue
                    if lenA == 0:
                        i_start = target_ia
                    else:
                        idx = bisect.bisect_right(startsA, target_ia) - 1
                        if idx < 0:
                            continue
                        i_start = startsA[idx]
                    j = jc + lenC - 1
                    if i_start > j:
                        continue
                    length = j - i_start + 1
                    if length < min_len:
                        min_len = length

        return min_len if min_len != float('inf') else -1

# @lc code=end
