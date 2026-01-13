#
# @lc app=leetcode id=3504 lang=python3
#
# [3504] Longest Palindrome After Substring Concatenation II
#
# @lc code=start
class SparseTableMax:
    def __init__(self, arr):
        self.arr = arr
        n = len(arr)
        self.log = [0] * (n + 1)
        for i in range(2, n + 1):
            self.log[i] = self.log[i // 2] + 1

        st = [arr[:]]
        k = 1
        while (1 << k) <= n:
            prev = st[-1]
            span = 1 << k
            half = span >> 1
            row_len = n - span + 1
            cur = [0] * row_len
            for i in range(row_len):
                a = prev[i]
                b = prev[i + half]
                cur[i] = a if a >= b else b
            st.append(cur)
            k += 1
        self.st = st

    def query(self, l, r):
        if l > r:
            return -10**18
        length = r - l + 1
        k = self.log[length]
        a = self.st[k][l]
        b = self.st[k][r - (1 << k) + 1]
        return a if a >= b else b


class Solution:
    def _best_start_end_pal(self, x: str):
        n = len(x)
        bestStart = [0] * (n + 1)  # bestStart[n]=0 for convenience (empty)
        bestEnd = [0] * n
        bestAll = 1

        for c in range(n):
            # odd length palindromes
            l = r = c
            while l >= 0 and r < n and x[l] == x[r]:
                length = r - l + 1
                if length > bestStart[l]:
                    bestStart[l] = length
                if length > bestEnd[r]:
                    bestEnd[r] = length
                if length > bestAll:
                    bestAll = length
                l -= 1
                r += 1

            # even length palindromes
            l, r = c, c + 1
            while l >= 0 and r < n and x[l] == x[r]:
                length = r - l + 1
                if length > bestStart[l]:
                    bestStart[l] = length
                if length > bestEnd[r]:
                    bestEnd[r] = length
                if length > bestAll:
                    bestAll = length
                l -= 1
                r += 1

        # every position has at least length-1 palindrome (single char)
        # but expansions already cover that; still ensure:
        for i in range(n):
            if bestStart[i] == 0:
                bestStart[i] = 1
            if bestEnd[i] == 0:
                bestEnd[i] = 1
        bestStart[n] = 0
        return bestStart, bestEnd, bestAll

    def longestPalindrome(self, s: str, t: str) -> int:
        n, m = len(s), len(t)

        bestStartS, _, bestS = self._best_start_end_pal(s)
        _, bestEndT, bestT = self._best_start_end_pal(t)

        ans = bestS if bestS >= bestT else bestT

        # Build RMQ for HS[x] = bestStartS[x] + 2*x, for x in [0..n]
        HS = [bestStartS[x] + 2 * x for x in range(n + 1)]
        rmqS = SparseTableMax(HS)

        # Build RMQ for HT over y in [-1..m-1] with shift:
        # index 0 corresponds to y=-1 and bestEnd=0 => value = 0 - 2*(-1) = 2
        # index (y+1) corresponds to y
        HT = [0] * (m + 1)
        HT[0] = 2
        for y in range(m):
            HT[y + 1] = bestEndT[y] - 2 * y
        rmqT = SparseTableMax(HT)

        rt = t[::-1]

        # DP for LCP between s[i:] and rt[p:]
        prev = [0] * (m + 1)
        for i in range(n - 1, -1, -1):
            cur = [0] * (m + 1)
            si = s[i]
            for p in range(m - 1, -1, -1):
                if si == rt[p]:
                    L = 1 + prev[p + 1]
                    cur[p] = L

                    j = m - 1 - p  # ending index in t

                    # Core in s: maximize over x=i+k, k in [1..L]
                    lS = i + 1
                    rS = i + L
                    if rS > n:
                        rS = n
                    if lS <= rS:
                        candA = rmqS.query(lS, rS) - 2 * i
                        if candA > ans:
                            ans = candA

                    # Core in t: maximize over y=j-k, k in [1..L] => y in [j-L..j-1]
                    yl = j - L
                    if yl < -1:
                        yl = -1
                    yr = j - 1
                    if yl <= yr:
                        maxHT = rmqT.query(yl + 1, yr + 1)
                        candB = 2 * j + maxHT
                        if candB > ans:
                            ans = candB
                else:
                    cur[p] = 0
            prev = cur

        return ans
# @lc code=end
