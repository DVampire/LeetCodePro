#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        import sys
        sys.setrecursionlimit(10000)
        
        n = len(grid)
        m = len(grid[0])
        
        # Directions: down-right, down-left, up-left, up-right
        directions = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
        
        memo = {}
        
        def dfs(i, j, d, expected_val, turned):
            if not (0 <= i < n and 0 <= j < m):
                return 0
            if grid[i][j] != expected_val:
                return 0
            
            key = (i, j, d, expected_val, turned)
            if key in memo:
                return memo[key]
            
            dr, dc = directions[d]
            ni, nj = i + dr, j + dc
            
            # Next expected value in the sequence
            if expected_val == 1:
                nv = 2
            elif expected_val == 2:
                nv = 0
            else:  # expected_val == 0
                nv = 2
            
            # Option 1: Continue without turning
            result = 1 + dfs(ni, nj, d, nv, turned)
            
            # Option 2: Turn (if we haven't turned yet)
            if not turned:
                new_d = (d + 1) % 4
                dr2, dc2 = directions[new_d]
                ni2, nj2 = i + dr2, j + dc2
                result = max(result, 1 + dfs(ni2, nj2, new_d, nv, True))
            
            memo[key] = result
            return result
        
        ans = 0
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    for d in range(4):
                        ans = max(ans, dfs(i, j, d, 1, False))
        
        return ans
# @lc code=end