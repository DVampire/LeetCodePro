#
# @lc app=leetcode id=3777 lang=python3
#
# [3777] Minimum Deletions to Make Alternating Substring
#

from typing import List

# @lc code=start
class Fenwick:
    def __init__(self, n: int):
        self.n = n
        self.bit = [0] * (n + 1)

    def add(self, i: int, delta: int) -> None:
        # i is 1-based
        while i <= self.n:
            self.bit[i] += delta
            i += i & -i

    def sum(self, i: int) -> int:
        # prefix sum up to i (1-based), sum(0) = 0
        res = 0
        while i > 0:
            res += self.bit[i]
            i -= i & -i
        return res

    def range_sum(self, l: int, r: int) -> int:
        # sum over [l, r], 1-based
        if l > r:
            return 0
        return self.sum(r) - self.sum(l - 1)


class Solution:
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        s = list(s)

        # e[i] for i in [1..n-1]: 1 if s[i]==s[i-1]
        e = [0] * n
        fw = Fenwick(n)  # we will only use indices 1..n-1
        for i in range(1, n):
            e[i] = 1 if s[i] == s[i - 1] else 0
            if e[i]:
                fw.add(i, e[i])

        ans = []

        def recompute(idx: int) -> None:
            # idx in [1..n-1]
            nonlocal e
            new_val = 1 if s[idx] == s[idx - 1] else 0
            if new_val != e[idx]:
                fw.add(idx, new_val - e[idx])
                e[idx] = new_val

        for q in queries:
            if q[0] == 1:
                j = q[1]
                s[j] = 'A' if s[j] == 'B' else 'B'
                if 1 <= j <= n - 1:
                    recompute(j)
                if 1 <= j + 1 <= n - 1:
                    recompute(j + 1)
            else:
                l, r = q[1], q[2]
                if l == r:
                    ans.append(0)
                else:
                    # sum of e in indices [l+1..r]
                    ans.append(fw.range_sum(l + 1, r))

        return ans
# @lc code=end
