#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])
        
        # Directions: 0: DR, 1: DL, 2: UL, 3: UR
        dr = [1, 1, -1, -1]
        dc = [1, -1, -1, 1]
        
        # dp1[d][r][c]: max length starting at (r, c) in direction d (already turned)
        # dp0[d][r][c]: max length starting at (r, c) in direction d (can still turn)
        dp1 = [[[0] * m for _ in range(n)] for _ in range(4)]
        dp0 = [[[0] * m for _ in range(n)] for _ in range(4)]
        
        # Precompute dp1
        for d in range(4):
            rows = range(n - 1, -1, -1) if dr[d] == 1 else range(n)
            cols = range(m - 1, -1, -1) if dc[d] == 1 else range(m)
            for r in rows:
                for c in cols:
                    if grid[r][c] == 1: continue
                    target = 2 - grid[r][c]
                    nr, nc = r + dr[d], c + dc[d]
                    if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] == target:
                        dp1[d][r][c] = 1 + dp1[d][nr][nc]
                    else:
                        dp1[d][r][c] = 1
                        
        # Precompute dp0
        for d in range(4):
            nd = (d + 1) % 4
            rows = range(n - 1, -1, -1) if dr[d] == 1 else range(n)
            cols = range(m - 1, -1, -1) if dc[d] == 1 else range(m)
            for r in rows:
                for c in cols:
                    if grid[r][c] == 1: continue
                    target = 2 - grid[r][c]
                    res = dp1[nd][r][c]
                    nr, nc = r + dr[d], c + dc[d]
                    if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] == target:
                        res = max(res, 1 + dp0[d][nr][nc])
                    dp0[d][r][c] = res
                    
        ans = 0
        for r in range(n):
            for c in range(m):
                if grid[r][c] == 1:
                    ans = max(ans, 1)
                    for d in range(4):
                        nr, nc = r + dr[d], c + dc[d]
                        if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] == 2:
                            ans = max(ans, 1 + dp0[d][nr][nc])
                            
        return ans
# @lc code=end