#
# @lc app=leetcode id=3594 lang=python3
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
import heapq
import math
from itertools import combinations

class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        # Precompute all possible subsets that can fit in the boat
        possible_subsets = []
        for size in range(1, k + 1):
            for indices in combinations(range(n), size):
                sub_mask = 0
                max_t = 0
                for i in indices:
                    sub_mask |= (1 << i)
                    if time[i] > max_t:
                        max_t = time[i]
                possible_subsets.append((sub_mask, max_t))
        
        # target_mask: everyone is at the destination
        target_mask = (1 << n) - 1
        
        # dist[mask][stage][side] stores the minimum time
        # side 0: base camp, side 1: destination
        dist = {}
        
        # Priority queue for Dijkstra: (current_time, mask, stage, side)
        pq = [(0.0, 0, 0, 0)]
        dist[(0, 0, 0)] = 0.0
        
        while pq:
            d, mask, stage, side = heapq.heappop(pq)
            
            if d > dist.get((mask, stage, side), float('inf')):
                continue
            
            # If everyone is at the destination and the boat just arrived
            if mask == target_mask and side == 1:
                return d
            
            if side == 0:  # Boat is at base camp
                # Try all possible groups to send to destination
                for sub_mask, max_t in possible_subsets:
                    # Only pick people who are currently at the base camp
                    if not (mask & sub_mask):
                        new_mask = mask | sub_mask
                        trip_time = max_t * mul[stage]
                        new_stage = (stage + math.floor(trip_time + 1e-9)) % m
                        new_dist = d + trip_time
                        
                        if new_dist < dist.get((new_mask, new_stage, 1), float('inf')):
                            dist[(new_mask, new_stage, 1)] = new_dist
                            heapq.heappush(pq, (new_dist, new_mask, new_stage, 1))
            
            else:  # Boat is at destination (and mask != target_mask)
                # Exactly one person must return if individuals are left behind
                for i in range(n):
                    if mask & (1 << i):
                        new_mask = mask ^ (1 << i)
                        return_time = time[i] * mul[stage]
                        new_stage = (stage + math.floor(return_time + 1e-9)) % m
                        new_dist = d + return_time
                        
                        if new_dist < dist.get((new_mask, new_stage, 0), float('inf')):
                            dist[(new_mask, new_stage, 0)] = new_dist
                            heapq.heappush(pq, (new_dist, new_mask, new_stage, 0))
                            
        return -1.0
# @lc code=end