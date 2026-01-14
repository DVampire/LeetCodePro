#
# @lc app=leetcode id=3609 lang=python3
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
class Solution:
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        if sx == tx and sy == ty:
            return 0
        
        moves = 0
        while tx > sx or ty > sy:
            if tx < sx or ty < sy:
                return -1
            
            if tx == ty:
                # Special case: came from (0, ty) or (tx, 0)
                if sy == ty and ty > 0 and sx % ty == 0:
                    return moves + 1 + sx // ty
                if sx == tx and tx > 0 and sy % tx == 0:
                    return moves + 1 + sy // tx
                return -1
            
            if tx > ty:
                if ty == sy:
                    max_val = max(sx, sy)
                    if max_val == 0:
                        return moves if tx == sx else -1
                    if (tx - sx) % max_val == 0:
                        return moves + (tx - sx) // max_val
                    else:
                        return -1
                steps = max(1, (tx - sx) // ty)
                moves += steps
                tx -= steps * ty
            else:  # ty > tx
                if tx == sx:
                    max_val = max(sx, sy)
                    if max_val == 0:
                        return moves if ty == sy else -1
                    if (ty - sy) % max_val == 0:
                        return moves + (ty - sy) // max_val
                    else:
                        return -1
                steps = max(1, (ty - sy) // tx)
                moves += steps
                ty -= steps * tx
        
        return moves if tx == sx and ty == sy else -1
# @lc code=end