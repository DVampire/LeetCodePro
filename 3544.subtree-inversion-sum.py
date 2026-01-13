#
# @lc app=leetcode id=3544 lang=python3
#
# [3544] Subtree Inversion Sum
#

from typing import List
from array import array

# @lc code=start
class Solution:
    def subtreeInversionSum(self, edges: List[List[int]], nums: List[int], k: int) -> int:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        # Root the tree at 0, build children and a traversal order
        children = [[] for _ in range(n)]
        parent = [-1] * n
        parent[0] = 0
        stack = [0]
        order = []
        while stack:
            u = stack.pop()
            order.append(u)
            for v in adj[u]:
                if v == parent[u]:
                    continue
                parent[v] = u
                children[u].append(v)
                stack.append(v)

        kk = k
        stride_par = kk + 1  # indices 1..k used
        stride_node = 2 * stride_par

        # dp is a flat int64 array: dp[u][p][t] at index u*stride_node + p*stride_par + t
        dp = array('q', [0]) * (n * stride_node)

        dpar = stride_par
        dnode = stride_node
        dp_arr = dp  # local alias

        for u in reversed(order):
            # Sum children dp-vectors for each parity separately:
            # S0[d] = sum over children c of dp[c][0][d]
            # S1[d] = sum over children c of dp[c][1][d]
            S0 = [0] * (kk + 1)
            S1 = [0] * (kk + 1)
            for ch in children[u]:
                basec = ch * dnode
                off0c = basec
                off1c = basec + dpar
                for d in range(1, kk + 1):
                    S0[d] += dp_arr[off0c + d]
                    S1[d] += dp_arr[off1c + d]

            base = u * dnode
            off0 = base
            off1 = base + dpar
            num = nums[u]

            # parity p = 0
            nodeVal0 = num
            for t in range(1, kk):
                dp_arr[off0 + t] = nodeVal0 + S0[t + 1]
            dp_arr[off0 + kk] = nodeVal0 + S0[kk]
            # invert at u if allowed (t == k): toggles parity for subtree
            inv0 = -num + S1[1]
            if inv0 > dp_arr[off0 + kk]:
                dp_arr[off0 + kk] = inv0

            # parity p = 1
            nodeVal1 = -num
            for t in range(1, kk):
                dp_arr[off1 + t] = nodeVal1 + S1[t + 1]
            dp_arr[off1 + kk] = nodeVal1 + S1[kk]
            inv1 = num + S0[1]
            if inv1 > dp_arr[off1 + kk]:
                dp_arr[off1 + kk] = inv1

        # initial state at root: parity 0, distance capped at k
        return dp_arr[0 * dnode + 0 * dpar + kk]
# @lc code=end
