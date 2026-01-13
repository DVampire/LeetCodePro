#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
from typing import List
import heapq

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return 0

        val = nums[:]  # current values per node id
        left = [i - 1 for i in range(n)]
        right = [i + 1 for i in range(n)]
        right[-1] = -1
        ver = [0] * n
        alive = [True] * n

        def violation(i: int, j: int) -> int:
            return 1 if val[i] > val[j] else 0

        # count initial adjacent inversions
        inv = 0
        for i in range(n - 1):
            if val[i] > val[i + 1]:
                inv += 1

        # heap of (sum, left_id, right_id, ver_left, ver_right)
        heap = []

        def push_pair(i: int) -> None:
            j = right[i]
            if j != -1 and alive[i] and alive[j]:
                heapq.heappush(heap, (val[i] + val[j], i, j, ver[i], ver[j]))

        for i in range(n - 1):
            push_pair(i)

        ops = 0
        while inv > 0:
            # get the valid minimum-sum adjacent pair
            while True:
                s, i, j, vi, vj = heap[0]
                if (not alive[i]) or (not alive[j]) or right[i] != j or ver[i] != vi or ver[j] != vj:
                    heapq.heappop(heap)
                    continue
                break

            heapq.heappop(heap)
            # merge i and j (j = right[i])
            a, b = i, j
            la = left[a]
            rb = right[b]

            # remove old violations on affected boundaries
            if la != -1:
                inv -= violation(la, a)
            inv -= violation(a, b)
            if rb != -1:
                inv -= violation(b, rb)

            # perform merge: keep node a, delete node b
            val[a] += val[b]
            ver[a] += 1

            alive[b] = False
            ver[b] += 1

            right[a] = rb
            if rb != -1:
                left[rb] = a

            # add new violations after merge
            if la != -1:
                inv += violation(la, a)
            if rb != -1:
                inv += violation(a, rb)

            # push updated adjacent pairs
            if la != -1:
                push_pair(la)  # (la, a) sum changed because a changed
            if rb != -1:
                push_pair(a)   # (a, rb) newly formed

            ops += 1

        return ops
# @lc code=end
