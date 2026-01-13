#
# @lc app=leetcode id=3569 lang=python3
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
from typing import List
from collections import defaultdict
import heapq

class SegTree:
    def __init__(self, n: int):
        self.n = n
        self.mx = [0] * (4 * n)
        self.lazy = [0] * (4 * n)

    def _apply(self, node: int, val: int):
        self.mx[node] += val
        self.lazy[node] += val

    def _push(self, node: int):
        if self.lazy[node] != 0:
            v = self.lazy[node]
            self._apply(node * 2, v)
            self._apply(node * 2 + 1, v)
            self.lazy[node] = 0

    def add(self, L: int, R: int, val: int):
        if L > R or self.n <= 0:
            return
        self._add(1, 1, self.n, L, R, val)

    def _add(self, node: int, nl: int, nr: int, L: int, R: int, val: int):
        if L <= nl and nr <= R:
            self._apply(node, val)
            return
        self._push(node)
        mid = (nl + nr) // 2
        if L <= mid:
            self._add(node * 2, nl, mid, L, R, val)
        if R > mid:
            self._add(node * 2 + 1, mid + 1, nr, L, R, val)
        self.mx[node] = self.mx[node * 2] if self.mx[node * 2] > self.mx[node * 2 + 1] else self.mx[node * 2 + 1]

    def max_all(self) -> int:
        return self.mx[1] if self.n > 0 else 0


class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        m = n - 1  # split positions k in [1..n-1]

        maxV = 100000
        # Sieve of Eratosthenes
        is_prime = [True] * (maxV + 1)
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(maxV ** 0.5) + 1):
            if is_prime[i]:
                step = i
                start = i * i
                is_prime[start:maxV + 1:step] = [False] * (((maxV - start) // step) + 1)

        # prime value -> (pos_set, min_heap, max_heap)
        pos_set = defaultdict(set)
        min_heap = defaultdict(list)
        max_heap = defaultdict(list)

        def get_minmax(p: int):
            s = pos_set[p]
            if not s:
                return None, None
            hmin = min_heap[p]
            while hmin and hmin[0] not in s:
                heapq.heappop(hmin)
            hmax = max_heap[p]
            while hmax and (-hmax[0]) not in s:
                heapq.heappop(hmax)
            return hmin[0], -hmax[0]

        def interval_of(p: int):
            s = pos_set[p]
            if len(s) < 2:
                return None
            mn, mx = get_minmax(p)
            # crossing split k when mn < k <= mx => k in [mn+1, mx]
            return (mn + 1, mx)

        # Build initial structures
        for i, v in enumerate(nums):
            if v <= maxV and is_prime[v]:
                pos_set[v].add(i)
                heapq.heappush(min_heap[v], i)
                heapq.heappush(max_heap[v], -i)

        seg = SegTree(m)
        activePrimes = 0
        for p in list(pos_set.keys()):
            if pos_set[p]:
                activePrimes += 1
                inter = interval_of(p)
                if inter is not None:
                    L, R = inter
                    seg.add(L, R, 1)

        def modify_prime(p: int, idx: int, add_pos: bool):
            nonlocal activePrimes

            before_nonempty = len(pos_set[p]) > 0
            old_inter = interval_of(p)

            if add_pos:
                pos_set[p].add(idx)
                heapq.heappush(min_heap[p], idx)
                heapq.heappush(max_heap[p], -idx)
            else:
                pos_set[p].remove(idx)

            after_nonempty = len(pos_set[p]) > 0
            new_inter = interval_of(p)

            if old_inter is not None:
                seg.add(old_inter[0], old_inter[1], -1)
            if new_inter is not None:
                seg.add(new_inter[0], new_inter[1], 1)

            if not before_nonempty and after_nonempty:
                activePrimes += 1
            elif before_nonempty and not after_nonempty:
                activePrimes -= 1

        ans = []
        for idx, val in queries:
            old = nums[idx]
            if old <= maxV and is_prime[old]:
                modify_prime(old, idx, add_pos=False)

            nums[idx] = val
            if val <= maxV and is_prime[val]:
                modify_prime(val, idx, add_pos=True)

            ans.append(activePrimes + seg.max_all())

        return ans
# @lc code=end
