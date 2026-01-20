#
# @lc app=leetcode id=3776 lang=python3
#
# [3776] Minimum Moves to Balance Circular Array
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def minMoves(self, balance: List[int]) -> int:
        n = len(balance)
        S = sum(balance)
        if S < 0:
            return -1
        
        neg = -1
        D = 0
        for i in range(n):
            if balance[i] < 0:
                neg = i
                D = -balance[i]
                break
        if D == 0:
            return 0
        
        # Build chain: balance[(neg+1)%n], ..., balance[(neg-1)%n]
        chain = []
        for i in range(1, n):
            j = (neg + i) % n
            chain.append(balance[j])
        m = n - 1
        
        # Left: supply from chain[0]
        pref_left = [0] * (m + 1)
        for i in range(m):
            pref_left[i + 1] = pref_left[i] + chain[i]
        fullcost_left = [0] * (m + 1)
        for i in range(1, m + 1):
            fullcost_left[i] = fullcost_left[i - 1] + chain[i - 1] * (i - 1)
        
        # Right: supply from chain[m-1]
        pref_right = [0] * (m + 1)
        fullcost_right = [0] * (m + 1)
        for i in range(1, m + 1):
            amt = chain[m - i]
            pref_right[i] = pref_right[i - 1] + amt
            fullcost_right[i] = fullcost_right[i - 1] + amt * (i - 1)
        
        def get_cost(pref: List[int], fullcost: List[int], X: int, m: int) -> int:
            if X == 0:
                return 0
            r = bisect.bisect_left(pref, X, 1, m + 1)
            if r > m:
                return float('inf')
            prev = pref[r - 1]
            partial = X - prev
            return fullcost[r - 1] + partial * (r - 1)
        
        # Ternary search for min cost(R) + cost(D-R) + D
        min_moves = float('inf')
        l, r = 0, D
        while r - l > 3:
            m1 = l + (r - l) // 3
            m2 = r - (r - l) // 3
            fm1 = get_cost(pref_left, fullcost_left, m1, m) + get_cost(pref_right, fullcost_right, D - m1, m)
            fm2 = get_cost(pref_left, fullcost_left, m2, m) + get_cost(pref_right, fullcost_right, D - m2, m)
            if fm1 <= fm2:
                r = m2
            else:
                l = m1
        for cand in range(l, r + 1):
            cost = get_cost(pref_left, fullcost_left, cand, m) + get_cost(pref_right, fullcost_right, D - cand, m) + D
            if cost < min_moves:
                min_moves = cost
        return int(min_moves)
# @lc code=end
