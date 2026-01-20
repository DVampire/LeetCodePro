#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
import heapq
from typing import List

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)
        if n < 2:
            return 0
            
        # Doubly Linked List simulation arrays
        # next_node[i] points to the index of the right neighbor of i
        # prev_node[i] points to the index of the left neighbor of i
        next_node = list(range(1, n + 1))
        next_node[-1] = -1
        prev_node = list(range(-1, n - 1))
        
        # Current values of nodes
        values = list(nums)
        
        # Validity flag to handle lazy deletion/updates
        valid = [True] * n
        
        bad_count = 0
        pq = []
        
        # Initial population of heap and bad_count
        for i in range(n - 1):
            if values[i] > values[i+1]:
                bad_count += 1
            # Heap stores (sum, left_index, right_index)
            # Tie-breaking: min sum, then min left_index (leftmost)
            heapq.heappush(pq, (values[i] + values[i+1], i, i+1))
            
        ops = 0
        
        while bad_count > 0:
            # Extract valid minimum pair
            while True:
                if not pq:
                    return ops
                s, u, v = heapq.heappop(pq)
                # Check if nodes are still valid and adjacent
                if valid[u] and valid[v] and next_node[u] == v:
                    # Check if the sum is current (handles stale entries)
                    if values[u] + values[v] == s:
                        break
            
            # Perform merge operation
            ops += 1
            
            p = prev_node[u]
            nxt = next_node[v]
            
            # 1. Remove contribution of old edges to bad_count
            if p != -1 and values[p] > values[u]:
                bad_count -= 1
            if values[u] > values[v]:
                bad_count -= 1
            if nxt != -1 and values[v] > values[nxt]:
                bad_count -= 1
                
            # 2. Update structure (merge v into u)
            new_val = values[u] + values[v]
            values[u] = new_val
            valid[v] = False
            
            next_node[u] = nxt
            if nxt != -1:
                prev_node[nxt] = u
            # prev_node[u] remains p
            
            # 3. Add contribution of new edges to bad_count
            if p != -1 and values[p] > values[u]:
                bad_count += 1
            if nxt != -1 and values[u] > values[nxt]:
                bad_count += 1
                
            # 4. Push new adjacent sums to heap
            if p != -1:
                heapq.heappush(pq, (values[p] + values[u], p, u))
            if nxt != -1:
                heapq.heappush(pq, (values[u] + values[nxt], u, nxt))
                
        return ops
# @lc code=end