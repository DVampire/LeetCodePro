#
# @lc app=leetcode id=3753 lang=python3
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        def compute(N: int) -> int:
            S = [int(c) for c in str(N)]
            L = len(S)
            memo = {}
            
            def dp(pos: int, tight: int, prev: int, pprev: int) -> tuple[int, int]:
                key = (pos, tight, prev, pprev)
                if key in memo:
                    return memo[key]
                if pos == L:
                    return 0, 1
                ans_sum = 0
                ans_cnt = 0
                up = S[pos] if tight == 1 else 9
                for d in range(up + 1):
                    new_tight = 1 if tight == 1 and d == S[pos] else 0
                    if prev == -1:
                        if d == 0:
                            new_prev = -1
                            new_pprev = -1
                            contrib = 0
                        else:
                            new_prev = d
                            new_pprev = -1
                            contrib = 0
                    else:
                        contrib = 0
                        if pprev != -1:
                            if (prev > pprev and prev > d) or (prev < pprev and prev < d):
                                contrib = 1
                        new_pprev = prev
                        new_prev = d
                    sub_sum, sub_cnt = dp(pos + 1, new_tight, new_prev, new_pprev)
                    ans_sum += sub_sum + contrib * sub_cnt
                    ans_cnt += sub_cnt
                memo[key] = (ans_sum, ans_cnt)
                return memo[key]
            
            return dp(0, 1, -1, -1)[0]
        
        return compute(num2) - compute(num1 - 1)
# @lc code=end