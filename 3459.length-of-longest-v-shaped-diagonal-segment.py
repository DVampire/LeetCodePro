#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        
        # Directions: 0: BR, 1: BL, 2: TL, 3: TR
        # (row_change, col_change)
        dirs = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
        
        # Memoization table: [row][col][direction_index][can_turn]
        # Initialize with -1
        memo = [[[[-1] * 2 for _ in range(4)] for _ in range(m)] for _ in range(n)]

        def dfs(r, c, dir_idx, can_turn):
            if memo[r][c][dir_idx][can_turn] != -1:
                return memo[r][c][dir_idx][can_turn]
            
            current_val = grid[r][c]
            target = 2 if current_val == 0 else 0
            
            max_len = 1 # Count current node
            
            # Option 1: Continue in same direction
            dr, dc = dirs[dir_idx]
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] == target:
                max_len = max(max_len, 1 + dfs(nr, nc, dir_idx, can_turn))
            
            # Option 2: Make a 90-degree clockwise turn if allowed
            if can_turn:
                new_dir_idx = (dir_idx + 1) % 4
                dr_new, dc_new = dirs[new_dir_idx]
                nr_new, nc_new = r + dr_new, c + dc_new
                if 0 <= nr_new < n and 0 <= nc_new < m and grid[nr_new][nc_new] == target:
                    max_len = max(max_len, 1 + dfs(nr_new, nc_new, new_dir_idx, 0))
            
            memo[r][c][dir_idx][can_turn] = max_len
            return max_len

        ans = 0
        for r in range(n):
            for c in range(m):
                if grid[r][c] == 1:
                    ans = max(ans, 1)
                    # Try moving in all 4 diagonal directions from the '1'
                    for i in range(4):
                        dr, dc = dirs[i]
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] == 2:
                            # From the neighbor (which is 2), we allow 1 turn.
                            # The length is 1 (the '1' cell) + result of dfs from '2'
                            ans = max(ans, 1 + dfs(nr, nc, i, 1))
                            
        return ans
# @lc code=end