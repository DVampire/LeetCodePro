#
# @lc app=leetcode id=3449 lang=python3
#
# [3449] Maximize the Minimum Game Score
#

# @lc code=start
from typing import List

class Solution:
    def maxScore(self, points: List[int], m: int) -> int:
        n = len(points)
        min_p = min(points)

        def can(target: int) -> bool:
            if target == 0:
                return True

            # First move: -1 -> 0
            moves = 1
            if moves > m:
                return False

            # visits at current index i, and next index i+1 (built from operations at i)
            cnt_cur = 1  # visits[0]
            cnt_next = 0

            if n == 2:
                req0 = (target + points[0] - 1) // points[0]
                req1 = (target + points[1] - 1) // points[1]

                a = max(0, req0 - cnt_cur)  # need more visits to index 0 via back moves
                c = max(0, req1 - 0)        # need visits to index 1 via forward moves

                # End at index 0: forward=back=b
                b1 = max(a, c)
                total1 = moves + 2 * b1

                # End at index 1: forward=back+1=b+1
                b2 = max(a, c - 1, 0)
                total2 = moves + (2 * b2 + 1)

                return min(total1, total2) <= m

            # Process indices 0..n-3, ending each stage at i+1
            for i in range(n - 2 - 1):
                req_i = (target + points[i] - 1) // points[i]
                k = max(0, req_i - cnt_cur)

                moves += 2 * k + 1
                if moves > m:
                    return False

                cnt_next += k + 1  # visits gained at i+1

                # advance window
                cnt_cur = cnt_next
                cnt_next = 0

            # Now at index n-2 with cnt_cur visits; index n-1 not visited yet
            req_a = (target + points[n - 2] - 1) // points[n - 2]
            req_b = (target + points[n - 1] - 1) // points[n - 1]

            a = max(0, req_a - cnt_cur)
            c = max(0, req_b - 0)

            # End at n-2
            b1 = max(a, c)
            extra1 = 2 * b1

            # End at n-1
            b2 = max(a, c - 1, 0)
            extra2 = 2 * b2 + 1

            return moves + min(extra1, extra2) <= m

        lo, hi = 0, min_p * m
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if can(mid):
                lo = mid
            else:
                hi = mid - 1
        return lo
# @lc code=end
