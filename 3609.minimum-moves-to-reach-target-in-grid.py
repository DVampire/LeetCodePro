#
# @lc app=leetcode id=3609 lang=python3
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
from functools import lru_cache

class Solution:
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        INF = 10**18

        @lru_cache(None)
        def dfs(x: int, y: int) -> int:
            # reached start
            if x == sx and y == sy:
                return 0
            # cannot go below start in reverse (forward never decreases coordinates)
            if x < sx or y < sy:
                return INF

            if x == y:
                if x == 0:
                    return INF  # would have matched start above if start were (0,0)
                a = dfs(x, 0)
                b = dfs(0, x)
                best = min(a, b)
                return best + 1 if best < INF else INF

            if x > y:
                # last move must have increased x
                if y == 0:
                    if x % 2:
                        return INF
                    return 1 + dfs(x // 2, 0)
                if x >= 2 * y:
                    if x % 2:
                        return INF
                    return 1 + dfs(x // 2, y)
                else:
                    return 1 + dfs(x - y, y)
            else:
                # y > x, last move must have increased y
                if x == 0:
                    if y % 2:
                        return INF
                    return 1 + dfs(0, y // 2)
                if y >= 2 * x:
                    if y % 2:
                        return INF
                    return 1 + dfs(x, y // 2)
                else:
                    return 1 + dfs(x, y - x)

        ans = dfs(tx, ty)
        return -1 if ans >= INF else ans
# @lc code=end
