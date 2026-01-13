#
# @lc app=leetcode id=3721 lang=python3
#
# [3721] Longest Balanced Subarray II
#

# @lc code=start
from typing import List

class Fenwick:
    def __init__(self, n: int):
        self.n = n
        self.bit = [0] * (n + 1)

    def add(self, i: int, delta: int) -> None:
        n = self.n
        bit = self.bit
        while i <= n:
            bit[i] += delta
            i += i & -i

    def sum(self, i: int) -> int:
        s = 0
        bit = self.bit
        while i > 0:
            s += bit[i]
            i -= i & -i
        return s

    def range_sum(self, l: int, r: int) -> int:
        if l > r:
            return 0
        return self.sum(r) - self.sum(l - 1)


class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        n = len(nums)

        total = [0] * (4 * n)
        minSuf = [0] * (4 * n)
        maxSuf = [0] * (4 * n)

        def pull(idx: int) -> None:
            li = idx * 2
            ri = li + 1
            total[idx] = total[li] + total[ri]
            # suffix either starts in right, or starts in left (then add total of right)
            minSuf[idx] = min(minSuf[ri], minSuf[li] + total[ri])
            maxSuf[idx] = max(maxSuf[ri], maxSuf[li] + total[ri])

        def update(idx: int, l: int, r: int, pos: int, val: int) -> None:
            if l == r:
                total[idx] = val
                minSuf[idx] = val
                maxSuf[idx] = val
                return
            mid = (l + r) // 2
            if pos <= mid:
                update(idx * 2, l, mid, pos, val)
            else:
                update(idx * 2 + 1, mid + 1, r, pos, val)
            pull(idx)

        bit = Fenwick(n)
        last = {}  # value -> last index
        w_at = [0] * (n + 1)  # current w at position

        # Find the smallest i in [1..qr] s.t. sum(w[i..qr]) == -sumRight
        # Here we always call with sumRight=0 from the root.
        def find_leftmost(idx: int, l: int, r: int, qr: int, sumRight: int):
            if l > qr:
                return None
            if r <= qr:
                target = -sumRight
                if target < minSuf[idx] or target > maxSuf[idx]:
                    return None
                if l == r:
                    return l
                mid = (l + r) // 2
                # full coverage => right child fully included
                right_sum_included = total[idx * 2 + 1]
                res = find_leftmost(idx * 2, l, mid, qr, sumRight + right_sum_included)
                if res is not None:
                    return res
                return find_leftmost(idx * 2 + 1, mid + 1, r, qr, sumRight)
            else:
                mid = (l + r) // 2
                if qr <= mid:
                    return find_leftmost(idx * 2, l, mid, qr, sumRight)
                # qr is in the right child => left child fully included, right child partially
                right_sum_included = bit.range_sum(mid + 1, qr)
                res = find_leftmost(idx * 2, l, mid, qr, sumRight + right_sum_included)
                if res is not None:
                    return res
                return find_leftmost(idx * 2 + 1, mid + 1, r, qr, sumRight)

        ans = 0
        for i, x in enumerate(nums, 1):
            wt = 1 if (x % 2 == 0) else -1

            if x in last:
                p = last[x]
                if w_at[p] != 0:
                    bit.add(p, -w_at[p])
                    update(1, 1, n, p, 0)
                    w_at[p] = 0

            last[x] = i
            # set current position to wt
            if w_at[i] != wt:
                bit.add(i, wt - w_at[i])
                update(1, 1, n, i, wt)
                w_at[i] = wt

            start = find_leftmost(1, 1, n, i, 0)
            if start is not None:
                ans = max(ans, i - start + 1)

        return ans
# @lc code=end
