#
# @lc app=leetcode id=3420 lang=python3
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#

from typing import List


class SegTree:
    def __init__(self, arr: List[int]):
        self.arr = arr
        self.n = len(arr)
        self.tree = [0] * (4 * self.n)
        self.build(1, 0, self.n - 1)

    def build(self, node: int, start: int, end: int) -> None:
        if start == end:
            self.tree[node] = self.arr[start]
            return
        mid = (start + end) // 2
        self.build(2 * node, start, mid)
        self.build(2 * node + 1, mid + 1, end)
        self.tree[node] = max(self.tree[2 * node], self.tree[2 * node + 1])

    def first_greater(self, start: int, val: int) -> int:
        def helper(node: int, ns: int, ne: int, ql: int, qr: int, v: int) -> int:
            if ql > ne or qr < ns:
                return self.n
            if self.tree[node] <= v:
                return self.n
            if ns == ne:
                return ns
            mid = (ns + ne) // 2
            res = helper(2 * node, ns, mid, ql, qr, v)
            if res < self.n:
                return res
            return helper(2 * node + 1, mid + 1, ne, ql, qr, v)
        return helper(1, 0, self.n - 1, start, self.n - 1, val)


class Solution:
    def countNonDecreasingSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n == 0:
            return 0
        ps = [0] * (n + 1)
        for i in range(n):
            ps[i + 1] = ps[i] + nums[i]
        extend = [0] * n
        extend[n - 1] = n - 1
        for i in range(n - 2, -1, -1):
            extend[i] = extend[i + 1] if nums[i] <= nums[i + 1] else i
        st = SegTree(nums)
        total = 0
        for l in range(n):
            init_r = extend[l]
            if init_r == n - 1:
                total += n - l
                continue
            r_max = init_r
            tot_cost = 0
            cur_maxv = nums[init_r]
            cur_pos = init_r + 1
            while cur_pos < n:
                next_up = st.first_greater(cur_pos, cur_maxv)
                if next_up == cur_pos:
                    tot_cost += 0
                    r_max = max(r_max, cur_pos)
                    cur_maxv = nums[cur_pos]
                    cur_pos += 1
                    continue
                seg_len = next_up - cur_pos
                seg_cost = seg_len * cur_maxv - (ps[next_up] - ps[cur_pos])
                remain = k - tot_cost
                if seg_cost <= remain:
                    tot_cost += seg_cost
                    r_max = max(r_max, next_up - 1)
                    if next_up < n:
                        tot_cost += 0
                        r_max = max(r_max, next_up)
                        cur_maxv = nums[next_up]
                        cur_pos = next_up + 1
                else:
                    lo = 0
                    hi = seg_len
                    while lo < hi:
                        md = (lo + hi + 1) // 2
                        md_cost = md * cur_maxv - (ps[cur_pos + md] - ps[cur_pos])
                        if tot_cost + md_cost <= k:
                            lo = md
                        else:
                            hi = md - 1
                    r_max = max(r_max, cur_pos + lo - 1)
                    break
            total += r_max - l + 1
        return total

# @lc code=end
