#
# @lc app=leetcode id=3419 lang=python3
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
import collections

class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        # Build the reversed graph
        # rev_adj[v] contains (u, w) indicating an original edge u -> v with weight w
        rev_adj = [[] for _ in range(n)]
        unique_weights = set()
        
        for u, v, w in edges:
            rev_adj[v].append((u, w))
            unique_weights.add(w)
            
        sorted_weights = sorted(list(unique_weights))
        
        if not sorted_weights:
            return -1
            
        # Function to check if all nodes can reach node 0 (in original graph)
        # using only edges with weight <= limit.
        # This is equivalent to checking if node 0 can reach all nodes 
        # in the reversed graph.
        def check(limit):
            count = 1
            visited = [False] * n
            visited[0] = True
            queue = collections.deque([0])
            
            while queue:
                u = queue.popleft()
                for v, w in rev_adj[u]:
                    if w <= limit and not visited[v]:
                        visited[v] = True
                        count += 1
                        queue.append(v)
            return count == n

        # If even with the maximum available weight we cannot connect the graph, return -1
        if not check(sorted_weights[-1]):
            return -1
            
        # Binary Search for the minimum weight
        left, right = 0, len(sorted_weights) - 1
        ans = sorted_weights[-1]
        
        while left <= right:
            mid = (left + right) // 2
            val = sorted_weights[mid]
            if check(val):
                ans = val
                right = mid - 1
            else:
                left = mid + 1
                
        return ans
# @lc code=end