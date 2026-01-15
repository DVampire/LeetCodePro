#
# @lc app=leetcode id=3609 lang=python3
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
from collections import deque

class Solution:
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        if sx == tx and sy == ty:
            return 0
        
        if sx == 0 and sy == 0:
            return -1
        
        visited = {(tx, ty)}
        queue = deque([(tx, ty, 0)])
        
        while queue:
            x, y, dist = queue.popleft()
            
            prevs = []
            
            # Option 1: (x/2, y) if x is even and x >= 2y
            if x % 2 == 0 and x >= 2 * y and x > 0:
                prevs.append((x // 2, y))
            
            # Option 2: (x - y, y) if y <= x < 2y
            if y > 0 and y <= x < 2 * y:
                prevs.append((x - y, y))
            
            # Option 3: (x, y/2) if y is even and y >= 2x
            if y % 2 == 0 and y >= 2 * x and y > 0:
                prevs.append((x, y // 2))
            
            # Option 4: (x, y - x) if x <= y < 2x
            if x > 0 and x <= y < 2 * x:
                prevs.append((x, y - x))
            
            for px, py in prevs:
                if px < sx or py < sy:
                    continue
                if (px, py) == (sx, sy):
                    return dist + 1
                if (px, py) not in visited:
                    visited.add((px, py))
                    queue.append((px, py, dist + 1))
        
        return -1
# @lc code=end