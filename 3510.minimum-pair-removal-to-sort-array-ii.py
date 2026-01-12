#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
import heapq

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return 0
        
        # Use arrays to simulate a doubly linked list of nodes
        val = list(nums)
        prev = [i - 1 for i in range(n)]
        nxt = [i + 1 for i in range(n)]
        nxt[n-1] = -1
        valid = [True] * n
        
        def is_bad(idx):
            if idx == -1 or not valid[idx] or nxt[idx] == -1:
                return False
            return val[idx] > val[nxt[idx]]
        
        # Initial PQ and bad_pairs_count
        pq = []
        bad_pairs_count = 0
        for i in range(n - 1):
            heapq.heappush(pq, (val[i] + val[i+1], i, i+1))
            if val[i] > val[i+1]:
                bad_pairs_count += 1
        
        ops = 0
        while bad_pairs_count > 0 and pq:
            s, L_id, R_id = heapq.heappop(pq)
            
            # Validate the pair from the heap
            if not valid[L_id] or not valid[R_id] or nxt[L_id] != R_id or val[L_id] + val[R_id] != s:
                continue
            
            # Identify neighbors
            P_id = prev[L_id]
            N_id = nxt[R_id]
            
            # Remove impact of old pairs from bad_pairs_count
            if is_bad(P_id): bad_pairs_count -= 1
            if is_bad(L_id): bad_pairs_count -= 1
            if is_bad(R_id): bad_pairs_count -= 1
            
            # Merge L_id and R_id into L_id
            val[L_id] = s
            nxt[L_id] = N_id
            if N_id != -1:
                prev[N_id] = L_id
            valid[R_id] = False
            ops += 1
            
            # Add impact of new pairs to bad_pairs_count
            if is_bad(P_id): bad_pairs_count += 1
            if is_bad(L_id): bad_pairs_count += 1
            
            # Push new potential pairs into PQ
            if P_id != -1:
                heapq.heappush(pq, (val[P_id] + val[L_id], P_id, L_id))
            if N_id != -1:
                heapq.heappush(pq, (val[L_id] + val[N_id], L_id, N_id))
                
        return ops
# @lc code=end