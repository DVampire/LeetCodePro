#
# @lc app=leetcode id=3534 lang=python3
#
# [3534] Path Existence Queries in a Graph II
#

from typing import List

# @lc code=start
class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[int]:
        sorted_nodes = sorted(range(n), key=lambda x: nums[x])
        pos = [0] * n
        for r, node in enumerate(sorted_nodes):
            pos[node] = r
        
        # Compute right_reach
        right_reach = [0] * n
        j = 0
        for i in range(n):
            while j < n and nums[sorted_nodes[j]] <= nums[sorted_nodes[i]] + maxDiff:
                j += 1
            right_reach[i] = j - 1
        
        # Compute comp_rank
        comp_rank = [0] * n
        cid = 0
        comp_rank[0] = 0
        for i in range(1, n):
            if nums[sorted_nodes[i]] - nums[sorted_nodes[i - 1]] > maxDiff:
                cid += 1
            comp_rank[i] = cid
        
        # Binary lifting for right_reach iterations
        LOG = 18
        jump = [[0] * n for _ in range(LOG)]
        for i in range(n):
            jump[0][i] = right_reach[i]
        for k in range(1, LOG):
            for i in range(n):
                mid = jump[k - 1][i]
                jump[k][i] = jump[k - 1][mid]
        
        ans = []
        for u, v in queries:
            if u == v:
                ans.append(0)
                continue
            p1 = pos[u]
            p2 = pos[v]
            if p1 > p2:
                p1, p2 = p2, p1
            if comp_rank[p1] != comp_rank[p2]:
                ans.append(-1)
                continue
            # Binary search minimal m
            l, h = 1, n
            while l < h:
                m = (l + h) // 2
                cur = p1
                reached = False
                for k in range(LOG - 1, -1, -1):
                    if (1 << k) & m:
                        cur = jump[k][cur]
                        if cur >= p2:
                            reached = True
                            break
                if reached or cur >= p2:
                    h = m
                else:
                    l = m + 1
            ans.append(l)
        return ans
# @lc code=end