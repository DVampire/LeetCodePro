#
# @lc app=leetcode id=3534 lang=python3
#
# [3534] Path Existence Queries in a Graph II
#

# @lc code=start
class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[int]:
        from bisect import bisect_left, bisect_right
        
        # Sort nodes by their values
        sorted_indices = sorted(range(n), key=lambda x: nums[x])
        sorted_values = [nums[i] for i in sorted_indices]
        
        # Map from original index to position in sorted array
        pos = [0] * n
        for i, idx in enumerate(sorted_indices):
            pos[idx] = i
        
        # Compute reach_right[i] and reach_left[i]
        reach_right = [0] * n
        for i in range(n):
            target = sorted_values[i] + maxDiff
            reach_right[i] = bisect_right(sorted_values, target) - 1
        
        reach_left = [0] * n
        for i in range(n):
            target = sorted_values[i] - maxDiff
            reach_left[i] = bisect_left(sorted_values, target)
        
        # Binary lifting for rightward jumps
        LOG = 18
        jump_right = [[0] * n for _ in range(LOG)]
        cnt_right = [[0] * n for _ in range(LOG)]
        
        for i in range(n):
            if reach_right[i] > i:
                jump_right[0][i] = reach_right[i]
                cnt_right[0][i] = 1
            else:
                jump_right[0][i] = i
                cnt_right[0][i] = 0
        
        for k in range(1, LOG):
            for i in range(n):
                j = jump_right[k-1][i]
                jump_right[k][i] = jump_right[k-1][j]
                cnt_right[k][i] = cnt_right[k-1][i] + cnt_right[k-1][j]
        
        # Binary lifting for leftward jumps
        jump_left = [[0] * n for _ in range(LOG)]
        cnt_left = [[0] * n for _ in range(LOG)]
        
        for i in range(n):
            if reach_left[i] < i:
                jump_left[0][i] = reach_left[i]
                cnt_left[0][i] = 1
            else:
                jump_left[0][i] = i
                cnt_left[0][i] = 0
        
        for k in range(1, LOG):
            for i in range(n):
                j = jump_left[k-1][i]
                jump_left[k][i] = jump_left[k-1][j]
                cnt_left[k][i] = cnt_left[k-1][i] + cnt_left[k-1][j]
        
        # Answer queries
        results = []
        for u, v in queries:
            pu, pv = pos[u], pos[v]
            if pu == pv:
                results.append(0)
                continue
            
            if pu < pv:
                # Going right
                jumps = 0
                curr = pu
                for k in range(LOG - 1, -1, -1):
                    if jump_right[k][curr] < pv:
                        jumps += cnt_right[k][curr]
                        curr = jump_right[k][curr]
                
                if reach_right[curr] >= pv:
                    results.append(jumps + 1)
                else:
                    results.append(-1)
            else:
                # Going left (pu > pv)
                jumps = 0
                curr = pu
                for k in range(LOG - 1, -1, -1):
                    if jump_left[k][curr] > pv:
                        jumps += cnt_left[k][curr]
                        curr = jump_left[k][curr]
                
                if reach_left[curr] <= pv:
                    results.append(jumps + 1)
                else:
                    results.append(-1)
        
        return results
# @lc code=end