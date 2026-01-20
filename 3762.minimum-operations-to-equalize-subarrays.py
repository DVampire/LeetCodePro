#
# @lc app=leetcode id=3762 lang=python3
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def minOperations(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        mods = [num % k for num in nums]
        M = [num // k for num in nums]
        prefix_M = [0] * (n + 1)
        for i in range(n):
            prefix_M[i + 1] = prefix_M[i] + M[i]

        # Sparse table for min/max on mods
        LOG = 17
        st_min = [[0] * n for _ in range(LOG)]
        st_max = [[0] * n for _ in range(LOG)]
        for i in range(n):
            st_min[0][i] = mods[i]
            st_max[0][i] = mods[i]
        for j in range(1, LOG):
            pw = 1 << j
            for i in range(n - pw + 1):
                st_min[j][i] = min(st_min[j - 1][i], st_min[j - 1][i + (pw >> 1)])
                st_max[j][i] = max(st_max[j - 1][i], st_max[j - 1][i + (pw >> 1)])

        # logg for sparse queries
        logg = [0] * (n + 2)
        for i in range(2, n + 1):
            logg[i] = logg[i // 2] + 1

        # Merge sort tree
        tree = [[] for _ in range(4 * n)]
        prefixs = [[] for _ in range(4 * n)]

        def build(node: int, start: int, end: int) -> None:
            if start == end:
                tree[node] = [M[start]]
                prefixs[node] = [0, M[start]]
                return
            mid = (start + end) // 2
            build(2 * node, start, mid)
            build(2 * node + 1, mid + 1, end)
            left = tree[2 * node]
            right = tree[2 * node + 1]
            merged_len = len(left) + len(right)
            merged = [0] * merged_len
            i = j = kk = 0
            while i < len(left) and j < len(right):
                if left[i] <= right[j]:
                    merged[kk] = left[i]
                    i += 1
                else:
                    merged[kk] = right[j]
                    j += 1
                kk += 1
            while i < len(left):
                merged[kk] = left[i]
                i += 1
                kk += 1
            while j < len(right):
                merged[kk] = right[j]
                j += 1
                kk += 1
            tree[node] = merged
            pref = [0] * (merged_len + 1)
            for ii in range(merged_len):
                pref[ii + 1] = pref[ii] + merged[ii]
            prefixs[node] = pref

        def _query(node: int, start: int, end: int, ql: int, qr: int, val: int) -> tuple[int, int]:
            if ql > end or qr < start:
                return 0, 0
            if ql <= start and end <= qr:
                lst = tree[node]
                p = bisect.bisect_right(lst, val)
                return p, prefixs[node][p]
            mid = (start + end) // 2
            lc, ls = _query(2 * node, start, mid, ql, qr, val)
            rc, rs = _query(2 * node + 1, mid + 1, end, ql, qr, val)
            return lc + rc, ls + rs

        def query_leq(ql: int, qr: int, val: int) -> tuple[int, int]:
            return _query(1, 0, n - 1, ql, qr, val)

        def find_med(ql: int, qr: int) -> int:
            sz = qr - ql + 1
            target = sz // 2 + 1
            low = 0
            high = 10**9 + 10
            while low < high:
                midv = low + (high - low) // 2
                cnt, _ = query_leq(ql, qr, midv)
                if cnt >= target:
                    high = midv
                else:
                    low = midv + 1
            return low

        build(1, 0, n - 1)

        ans = []
        for li, ri in queries:
            leng = ri - li + 1
            j = logg[leng]
            mn = min(st_min[j][li], st_min[j][ri - (1 << j) + 1])
            mx = max(st_max[j][li], st_max[j][ri - (1 << j) + 1])
            if mn != mx:
                ans.append(-1)
                continue
            total_s = prefix_M[ri + 1] - prefix_M[li]
            sz = leng
            med = find_med(li, ri)
            cnt_lt, sum_lt = query_leq(li, ri, med - 1)
            cnt_leq, sum_leq = query_leq(li, ri, med)
            cnt_gt = sz - cnt_leq
            sum_gt = total_s - sum_leq
            cost = cnt_lt * med - sum_lt + sum_gt - cnt_gt * med
            ans.append(cost)
        return ans

# @lc code=end
