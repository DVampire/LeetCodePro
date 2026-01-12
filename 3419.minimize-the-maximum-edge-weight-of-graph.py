#
# @lc app=leetcode id=3419 lang=python3
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
from typing import List
import collections

class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        # Build reversed adjacency list: actual edge u -> v becomes v -> u
        # This allows us to check if node 0 can reach all other nodes.
        adj = collections.defaultdict(list)
        max_w = 0
        for u, v, w in edges:
            adj[v].append((u, w))
            if w > max_w:
                max_w = w
        
        def can_reach_all(limit):
            visited = [False] * n
            visited[0] = True
            queue = collections.deque([0])
            count = 1
            
            while queue:
                curr = queue.popleft()
                for neighbor, weight in adj[curr]:
                    if not visited[neighbor] and weight <= limit:
                        visited[neighbor] = True
                        count += 1
                        queue.append(neighbor)
            
            return count == n

        # Binary search for the minimum possible maximum weight
        low = 1
        high = max_w
        ans = -1
        
        while low <= high:
            mid = (low + high) // 2
            if can_reach_all(mid):
                ans = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return ans
# @lc code=end