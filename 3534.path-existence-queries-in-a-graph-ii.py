#
# @lc app=leetcode id=3534 lang=python3
#
# [3534] Path Existence Queries in a Graph II
#

from typing import List

# @lc code=start
class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[int]:
        # Sort nodes by value
        order = sorted([(nums[i], i) for i in range(n)])
        val = [0] * n
        pos = [0] * n  # original index -> sorted position
        for p, (v, idx) in enumerate(order):
            val[p] = v
            pos[idx] = p

        # Connected components in sorted order split by gaps > maxDiff
        comp = [0] * n
        cid = 0
        for i in range(1, n):
            if val[i] - val[i - 1] > maxDiff:
                cid += 1
            comp[i] = cid

        # next[i] = farthest reachable index in 1 step (val[next[i]] - val[i] <= maxDiff)
        nxt = [0] * n
        r = 0
        for i in range(n):
            if r < i:
                r = i
            while r + 1 < n and val[r + 1] - val[i] <= maxDiff:
                r += 1
            nxt[i] = r

        # Binary lifting table
        LOG = (n).bit_length()
        up = [nxt[:]]
        for k in range(1, LOG):
            prev = up[k - 1]
            cur = [0] * n
            for i in range(n):
                cur[i] = prev[prev[i]]
            up.append(cur)

        ans = []
        for u, v in queries:
            if u == v:
                ans.append(0)
                continue
            i, j = pos[u], pos[v]
            if i > j:
                i, j = j, i
            if comp[i] != comp[j]:
                ans.append(-1)
                continue

            steps = 0
            cur = i
            for k in range(LOG - 1, -1, -1):
                jump_to = up[k][cur]
                if jump_to < j:
                    cur = jump_to
                    steps += 1 << k
            # one more jump reaches >= j
            ans.append(steps + 1)

        return ans
# @lc code=end
