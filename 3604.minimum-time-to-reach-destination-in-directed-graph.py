#
# @lc app=leetcode id=3604 lang=python3
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
import heapq

class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        # Adjacency list to store graph: u -> [(v, start, end)]
        graph = [[] for _ in range(n)]
        for u, v, start, end in edges:
            graph[u].append((v, start, end))
        
        # Priority queue for Dijkstra: (current_time, node)
        pq = [(0, 0)]
        
        # Min time to reach each node, initialized to infinity
        min_arrival = [float('inf')] * n
        min_arrival[0] = 0
        
        while pq:
            curr_time, u = heapq.heappop(pq)
            
            # If we reached the destination, return the time
            if u == n - 1:
                return curr_time
            
            # If we found a faster way to u already, skip
            if curr_time > min_arrival[u]:
                continue
            
            for v, start, end in graph[u]:
                # Calculate the earliest time we can take this edge
                # We must wait until at least 'start'.
                # If we arrive after 'start', we can take it immediately (wait time = 0).
                departure_time = max(curr_time, start)
                
                # Check if the departure time is within the valid window [start, end]
                if departure_time <= end:
                    arrival_time = departure_time + 1
                    
                    # If this path is faster than any previous path to v
                    if arrival_time < min_arrival[v]:
                        min_arrival[v] = arrival_time
                        heapq.heappush(pq, (arrival_time, v))
                        
        return -1
# @lc code=end