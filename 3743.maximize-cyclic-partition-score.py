#
# @lc app=leetcode id=3743 lang=python3
#
# [3743] Maximize Cyclic Partition Score
#

from typing import List

# @lc code=start
class SegTree:
    __slots__ = ("n", "mx", "lz")

    def __init__(self, n: int):
        self.n = n
        self.mx = [-(10**30)] * (4 * n)
        self.lz = [0] * (4 * n)

    def _push(self, idx: int):
        lz = self.lz[idx]
        if lz != 0:
            li = idx * 2
            ri = li + 1
            self.mx[li] += lz
            self.lz[li] += lz
            self.mx[ri] += lz
            self.lz[ri] += lz
            self.lz[idx] = 0

    def range_add(self, ql: int, qr: int, val: int):
        if ql > qr:
            return
        self._range_add(1, 0, self.n - 1, ql, qr, val)

    def _range_add(self, idx: int, l: int, r: int, ql: int, qr: int, val: int):
        if ql <= l and r <= qr:
            self.mx[idx] += val
            self.lz[idx] += val
            return
        self._push(idx)
        m = (l + r) // 2
        if ql <= m:
            self._range_add(idx * 2, l, m, ql, qr, val)
        if qr > m:
            self._range_add(idx * 2 + 1, m + 1, r, ql, qr, val)
        self.mx[idx] = self.mx[idx * 2] if self.mx[idx * 2] >= self.mx[idx * 2 + 1] else self.mx[idx * 2 + 1]

    def point_set(self, pos: int, val: int):
        self._point_set(1, 0, self.n - 1, pos, val)

    def _point_set(self, idx: int, l: int, r: int, pos: int, val: int):
        if l == r:
            self.mx[idx] = val
            self.lz[idx] = 0
            return
        self._push(idx)
        m = (l + r) // 2
        if pos <= m:
            self._point_set(idx * 2, l, m, pos, val)
        else:
            self._point_set(idx * 2 + 1, m + 1, r, pos, val)
        self.mx[idx] = self.mx[idx * 2] if self.mx[idx * 2] >= self.mx[idx * 2 + 1] else self.mx[idx * 2 + 1]

    def range_max(self, ql: int, qr: int) -> int:
        if ql > qr:
            return -(10**30)
        return self._range_max(1, 0, self.n - 1, ql, qr)

    def _range_max(self, idx: int, l: int, r: int, ql: int, qr: int) -> int:
        if ql <= l and r <= qr:
            return self.mx[idx]
        self._push(idx)
        m = (l + r) // 2
        res = -(10**30)
        if ql <= m:
            left = self._range_max(idx * 2, l, m, ql, qr)
            if left > res:
                res = left
        if qr > m:
            right = self._range_max(idx * 2 + 1, m + 1, r, ql, qr)
            if right > res:
                res = right
        return res


class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        k = min(k, n)

        # Fast path
        if k == 1:
            return max(nums) - min(nums)

        nums2 = nums + nums

        def solve_linear(arr: List[int]) -> int:
            NEG = -(10**30)
            # dp_prev[j] = best score for prefix length j with exactly (t-1) segments
            dp_prev = [NEG] * (n + 1)
            dp_prev[0] = 0
            best = 0

            for _ in range(1, k + 1):
                dp_next = [NEG] * (n + 1)
                st = SegTree(n)
                max_stack = []  # indices with decreasing values
                min_stack = []  # indices with increasing values

                for p in range(n):
                    # enable start at p (segment of length 1 has range 0)
                    st.point_set(p, dp_prev[p])
                    x = arr[p]

                    # update maxima contributions
                    while max_stack and arr[max_stack[-1]] <= x:
                        prev = max_stack.pop()
                        left = (max_stack[-1] + 1) if max_stack else 0
                        st.range_add(left, prev, x - arr[prev])
                    max_stack.append(p)

                    # update minima contributions
                    while min_stack and arr[min_stack[-1]] >= x:
                        prev = min_stack.pop()
                        left = (min_stack[-1] + 1) if min_stack else 0
                        st.range_add(left, prev, arr[prev] - x)
                    min_stack.append(p)

                    dp_next[p + 1] = st.range_max(0, p)

                dp_prev = dp_next
                if dp_prev[n] > best:
                    best = dp_prev[n]

            return best

        ans = 0
        # Try all rotations (correct but potentially heavy)
        for s in range(n):
            arr = nums2[s : s + n]
            val = solve_linear(arr)
            if val > ans:
                ans = val
        return ans
# @lc code=end
