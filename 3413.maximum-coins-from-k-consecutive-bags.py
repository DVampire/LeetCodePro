#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
from typing import List

class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        coins.sort()
        n = len(coins)
        minL = coins[0][0]
        maxR = max(r for _, r, _ in coins)

        # Build disjoint intervals including zero-coin gaps.
        intervals = []  # (l, r, c)
        intervals.append((minL - k, minL - 1, 0))  # leading zeros of length k
        prev_end = minL - 1

        for l, r, c in coins:
            if l > prev_end + 1:
                intervals.append((prev_end + 1, l - 1, 0))
            intervals.append((l, r, c))
            prev_end = r

        intervals.append((maxR + 1, maxR + k, 0))  # trailing zeros of length k

        def best_left_aligned(ints: List[tuple], k: int) -> int:
            # Assumes ints are sorted, disjoint, and cover enough range.
            m = len(ints)
            j = 0
            sum_len = 0
            sum_coins = 0
            ans = 0

            for i in range(m):
                if j < i:
                    j = i
                    sum_len = 0
                    sum_coins = 0

                while j < m and sum_len < k:
                    l, r, c = ints[j]
                    length = r - l + 1
                    sum_len += length
                    sum_coins += length * c
                    j += 1

                # With leading/trailing zeros of length k, we should always reach sum_len >= k
                if sum_len >= k:
                    last_c = ints[j - 1][2]
                    excess = sum_len - k
                    cur = sum_coins - excess * last_c
                    if cur > ans:
                        ans = cur

                # Slide left boundary past interval i
                l, r, c = ints[i]
                length = r - l + 1
                sum_len -= length
                sum_coins -= length * c

            return ans

        ans1 = best_left_aligned(intervals, k)

        # Reverse coordinate transform to convert "right-aligned" cases into "left-aligned".
        rev = [(-r, -l, c) for (l, r, c) in intervals]
        rev.sort(key=lambda x: x[0])
        ans2 = best_left_aligned(rev, k)

        return max(ans1, ans2)
# @lc code=end
