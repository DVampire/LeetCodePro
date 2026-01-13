#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#
# @lc code=start
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        max_len = 0
        
        # Four diagonal directions
        directions = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
        
        # 90-degree clockwise turn mapping
        clockwise_turn = {
            (1, 1): (1, -1),
            (1, -1): (-1, -1),
            (-1, -1): (-1, 1),
            (-1, 1): (1, 1)
        }
        
        # Expected sequence: 1, 2, 0, 2, 0, 2, 0, ...
        def get_expected(idx):
            if idx == 0:
                return 1
            elif idx % 2 == 1:
                return 2
            else:
                return 0
        
        # Try starting from each cell with value 1
        for i in range(n):
            for j in range(m):
                if grid[i][j] != 1:
                    continue
                
                # Try each starting direction
                for dr, dc in directions:
                    # Follow the direction and collect valid positions
                    positions = []
                    r, c = i, j
                    idx = 0
                    
                    while 0 <= r < n and 0 <= c < m and grid[r][c] == get_expected(idx):
                        positions.append((r, c))
                        idx += 1
                        r += dr
                        c += dc
                    
                    # No turn case
                    max_len = max(max_len, len(positions))
                    
                    # Try turning at each valid position
                    for turn_pos in range(len(positions)):
                        turn_r, turn_c = positions[turn_pos]
                        new_dr, new_dc = clockwise_turn[(dr, dc)]
                        
                        # Continue from the turn position with new direction
                        r, c = turn_r + new_dr, turn_c + new_dc
                        idx = turn_pos + 1
                        turn_length = turn_pos + 1
                        
                        while 0 <= r < n and 0 <= c < m and grid[r][c] == get_expected(idx):
                            turn_length += 1
                            idx += 1
                            r += new_dr
                            c += new_dc
                        
                        max_len = max(max_len, turn_length)
        
        return max_len
# @lc code=end