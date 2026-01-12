#
# @lc app=leetcode id=3534 lang=python3
#
# [3534] Path Existence Queries in a Graph II
#

# @lc code=start
import bisect

class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[int]:
        # Get unique sorted values
        U = sorted(list(set(nums)))
        K = len(U)
        val_to_idx = {val: i for i, val in enumerate(U)}
        
        # Precompute furthest reachable index for each value index
        R = [0] * K
        for i in range(K):
            # Find the largest index j such that U[j] <= U[i] + maxDiff
            R[i] = bisect.bisect_right(U, U[i] + maxDiff) - 1
        
        # Sparse table for binary lifting
        MAX_LOG = 18
        st = [R]
        for p in range(1, MAX_LOG):
            prev_st = st[p-1]
            curr_st = [prev_st[prev_st[i]] for i in range(K)]
            st.append(curr_st)
            
        # Precompute connected components of values
        comp = [0] * K
        curr_comp = 0
        for i in range(1, K):
            if U[i] - U[i-1] > maxDiff:
                curr_comp += 1
            comp[i] = curr_comp
            
        results = []
        for u, v in queries:
            if u == v:
                results.append(0)
                continue
            
            val_u, val_v = nums[u], nums[v]
            idx_u, idx_v = val_to_idx[val_u], val_to_idx[val_v]
            
            if idx_u == idx_v:
                # Same value but different nodes
                results.append(1)
                continue
            
            if idx_u > idx_v:
                idx_u, idx_v = idx_v, idx_u
            
            # Check if they are in the same connected component
            if comp[idx_u] != comp[idx_v]:
                results.append(-1)
                continue
            
            # Binary lifting to find minimum steps to reach idx_v starting from idx_u
            steps = 0
            curr = idx_u
            for p in range(MAX_LOG - 1, -1, -1):
                if st[p][curr] < idx_v:
                    curr = st[p][curr]
                    steps += (1 << p)
            
            # One more step is needed to reach or exceed idx_v
            results.append(steps + 1)
            
        return results
# @lc code=end