#
# @lc app=leetcode id=3594 lang=python3
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
import heapq
import math
from typing import List

class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        # Sort time so that indices correspond to speed (lower index = faster/same)
        # Actually, sorting helps us easily pick 'slowest' by picking largest indices.
        time.sort()
        
        # State: (mask, stage, boat_loc)
        # mask: bitmask of people at Base
        # stage: current stage index 0..m-1
        # boat_loc: 0 for Base, 1 for Dest
        
        # We map state (mask, stage, boat) to a linear index for the dist array
        # Index = (mask * m + stage) * 2 + boat
        size = (1 << n) * m * 2
        dist = [float('inf')] * size
        
        start_mask = (1 << n) - 1
        start_idx = (start_mask * m + 0) * 2 + 0
        dist[start_idx] = 0.0
        
        # PQ stores (current_time, mask, stage, boat_loc)
        pq = [(0.0, start_mask, 0, 0)]
        
        while pq:
            d, mask, stage, boat = heapq.heappop(pq)
            
            curr_idx = (mask * m + stage) * 2 + boat
            if d > dist[curr_idx]:
                continue
            
            # If everyone is at destination (mask 0) and boat is there (or doesn't matter, we are done)
            # The problem implies we just need to transport everyone. 
            # However, the boat must end up at destination if the last trip was Base->Dest.
            if mask == 0 and boat == 1:
                return d
            
            if boat == 0: # At Base, moving to Dest
                # Indices of people currently at Base
                at_base = [i for i in range(n) if (mask >> i) & 1]
                
                next_states = {} # new_mask -> trip_cost
                
                for idx_i, driver in enumerate(at_base):
                    driver_time = time[driver]
                    
                    # Strategy 1: Driver + fill with slowest available people
                    # We pick people with indices < driver (which are faster or equal)
                    # but we prefer the largest indices among them (slowest among them)
                    # to clear 'hard' people from base.
                    riders_mask = 0
                    rem = k - 1
                    for idx_x in range(idx_i - 1, -1, -1):
                        if rem == 0: break
                        riders_mask |= (1 << at_base[idx_x])
                        rem -= 1
                    
                    nm1 = mask ^ (1 << driver) ^ riders_mask
                    # Store/Update best cost for this mask
                    # Note: For a fixed mask transition, the driver is actually implicitly fixed 
                    # (it must be the max time person removed), so cost is fixed.
                    next_states[nm1] = driver_time
                    
                    if k > 1:
                        # Strategy 2: Driver + Specific Partner + fill with slowest
                        # We only need to try partners that were NOT included in Strategy 1.
                        # Strategy 1 includes indices at_base[idx_i-1 ... idx_i-(k-1)].
                        # So we check partners with index < idx_i - (k-1).
                        limit = idx_i - (k - 1)
                        if limit > 0:
                            for idx_j in range(limit):
                                partner = at_base[idx_j]
                                
                                current_group_mask = (1 << driver) | (1 << partner)
                                
                                # Fill remainder with slowest
                                rem2 = k - 2
                                riders_mask2 = 0
                                for idx_x in range(idx_i - 1, -1, -1):
                                    if rem2 == 0: break
                                    cand = at_base[idx_x]
                                    if cand == partner: continue
                                    riders_mask2 |= (1 << cand)
                                    rem2 -= 1
                                
                                nm2 = mask ^ current_group_mask ^ riders_mask2
                                next_states[nm2] = driver_time

                # Process transitions
                for nm, cost in next_states.items():
                    trip_time = cost * mul[stage]
                    new_time = d + trip_time
                    # Stage advances by floor(time)
                    new_stage = (stage + int(trip_time + 1e-9)) % m
                    
                    idx = (nm * m + new_stage) * 2 + 1
                    if new_time < dist[idx]:
                        dist[idx] = new_time
                        heapq.heappush(pq, (new_time, nm, new_stage, 1))
                        
            else: # At Dest, returning to Base
                # Indices of people currently at Dest (NOT in mask)
                at_dest = [i for i in range(n) if not ((mask >> i) & 1)]
                
                for r in at_dest:
                    return_time = time[r] * mul[stage]
                    new_time = d + return_time
                    new_stage = (stage + int(return_time + 1e-9)) % m
                    new_mask = mask | (1 << r)
                    
                    idx = (new_mask * m + new_stage) * 2 + 0
                    if new_time < dist[idx]:
                        dist[idx] = new_time
                        heapq.heappush(pq, (new_time, new_mask, new_stage, 0))
                        
        return -1.0
# @lc code=end