#
# @lc app=leetcode id=3615 lang=python3
#
# [3615] Longest Palindromic Path in Graph
#

# @lc code=start
from typing import List

class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        adj = [[] for _ in range(n)]
        dist = [[float('inf')] * n for _ in range(n)]
        for i in range(n): dist[i][i] = 0
        
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
            dist[u][v] = dist[v][u] = 1
            
        # Floyd-Warshall to find connectivity (needed for path existence)
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if dist[i][j] > dist[i][k] + dist[k][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]

        # dp[mask][u][v] = True if there exists a palindromic path using nodes in mask with ends u, v
        # Given n is very small, we can use a recursive approach with memoization
        memo = {}

        def solve(mask, u, v):
            state = (mask, u, v)
            if state in memo: return memo[state]
            
            # Base case: single node
            if u == v:
                return 1
            
            # Base case: length 2 (u and v are adjacent and labels match)
            if dist[u][v] == 1 and label[u] == label[v]:
                if (mask >> u & 1) and (mask >> v & 1):
                    return 2
            
            res = -float('inf')
            if label[u] == label[v]:
                # Try to find a smaller palindrome inside
                new_mask = mask ^ (1 << u) ^ (1 << v)
                for i in range(n):
                    if not (new_mask >> i & 1): continue
                    for j in range(n):
                        if not (new_mask >> j & 1): continue
                        # i must be neighbor of u, j must be neighbor of v
                        if dist[u][i] == 1 and dist[v][j] == 1:
                            inner = solve(new_mask, i, j)
                            if inner > 0:
                                res = max(res, inner + 2)
            
            memo[state] = res
            return res

        ans = 1
        # Iterate through all possible masks and endpoints
        # Since n is small, we can use a simpler approach: BFS/Iterative DP on length
        dp = {}
        # Length 1
        for i in range(n):
            dp[(1 << i, i, i)] = 1
        # Length 2
        for u, v in edges:
            if label[u] == label[v]:
                dp[(1 << u | 1 << v, u, v)] = 2
                ans = 2

        # Iterate by length
        for length in range(1, n + 1):
            current_states = [s for s, l in dp.items() if l == length]
            if not current_states: continue
            
            for mask, u, v in current_states:
                ans = max(ans, length)
                # Try to expand
                for ni in range(n):
                    if (mask >> ni) & 1: continue
                    if dist[ni][u] != 1: continue
                    for nj in range(n):
                        if (mask >> nj) & 1: continue
                        if ni == nj: continue
                        if dist[nj][v] != 1: continue
                        if label[ni] == label[nj]:
                            new_mask = mask | (1 << ni) | (1 << nj)
                            if (new_mask, ni, nj) not in dp or dp[(new_mask, ni, nj)] < length + 2:
                                dp[(new_mask, ni, nj)] = length + 2
                                
            # Odd extension: length + 1 if we can add just one node to make it even?
            # Actually, the palindrome logic handles even/odd separately.
            # Check if we can add one more node to the middle of a path for odd lengths
            for mask, u, v in current_states:
                for mid in range(n):
                    if (mask >> mid) & 1: continue
                    if dist[u][mid] == 1 and u == v:
                        # This is just length 1 -> 2, handled above
                        pass
        
        return max(dp.values()) if dp else 1

# @lc code=end