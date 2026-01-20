#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
from typing import List
class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        import sys
        sys.setrecursionlimit(10**5 + 10)
        n = len(parent)
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        new_parent = parent[:]
        path_map = {}

        def dfs(node: int, pmap: dict):
            if node != 0:
                y = pmap.get(s[node], None)
                if y is not None:
                    new_parent[node] = y
            old = pmap.get(s[node], None)
            pmap[s[node]] = node
            for child in adj[node]:
                dfs(child, pmap)
            if old is None:
                del pmap[s[node]]
            else:
                pmap[s[node]] = old

        dfs(0, path_map)

        new_adj = [[] for _ in range(n)]
        for i in range(1, n):
            p = new_parent[i]
            new_adj[p].append(i)

        answer = [0] * n
        def size_dfs(node: int) -> int:
            sz = 1
            for child in new_adj[node]:
                sz += size_dfs(child)
            answer[node] = sz
            return sz

        size_dfs(0)
        return answer
# @lc code=end