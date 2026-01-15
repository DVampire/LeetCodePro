#
# @lc app=leetcode id=3594 lang=python3
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
import heapq

class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        # Impossible case: boat holds 1 person but more than 1 need transport
        if k == 1 and n > 1:
            return -1.0
        
        all_transported = (1 << n) - 1
        dist = {}
        # (total_time, at_dest_bitmask, stage, boat_at_dest)
        pq = [(0.0, 0, 0, 0)]
        
        while pq:
            curr_time, at_dest, stage, boat_at_dest = heapq.heappop(pq)
            
            state = (at_dest, stage, boat_at_dest)
            if state in dist:
                continue
            dist[state] = curr_time
            
            # Check if all individuals transported
            if at_dest == all_transported:
                return curr_time
            
            if boat_at_dest == 0:  # Boat at base camp
                at_base = all_transported ^ at_dest
                # Enumerate all non-empty subsets of people at base
                subset = at_base
                while subset > 0:
                    if bin(subset).count('1') <= k:
                        # Calculate crossing time
                        max_t = max(time[i] for i in range(n) if subset & (1 << i))
                        trip_time = max_t * mul[stage]
                        new_at_dest = at_dest | subset
                        new_stage = (stage + int(trip_time) % m) % m
                        new_state = (new_at_dest, new_stage, 1)
                        if new_state not in dist:
                            heapq.heappush(pq, (curr_time + trip_time, new_at_dest, new_stage, 1))
                    subset = (subset - 1) & at_base
            else:  # Boat at destination - someone must return
                for r in range(n):
                    if at_dest & (1 << r):
                        ret_time = time[r] * mul[stage]
                        new_at_dest = at_dest & ~(1 << r)
                        new_stage = (stage + int(ret_time) % m) % m
                        new_state = (new_at_dest, new_stage, 0)
                        if new_state not in dist:
                            heapq.heappush(pq, (curr_time + ret_time, new_at_dest, new_stage, 0))
        
        return -1.0
# @lc code=end