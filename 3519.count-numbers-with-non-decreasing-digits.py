#
# @lc app=leetcode id=3519 lang=python3
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10**9 + 7

        def to_base_b(num: int, base: int) -> list[int]:
            if num == 0:
                return []
            digits = []
            while num > 0:
                digits.append(num % base)
                num //= base
            digits.reverse()
            return digits

        def count_up_to(D: list[int], base: int) -> int:
            L = len(D)
            memo = {}

            def dfs(pos: int, prev: int, tight: int, started: int) -> int:
                if pos == L:
                    return 1 if started else 0
                key = (pos, prev, tight, started)
                if key in memo:
                    return memo[key]
                ans = 0
                up = D[pos] if tight else base - 1
                for d in range(up + 1):
                    new_tight = 1 if tight and d == up else 0
                    if started == 0:
                        if d == 0:
                            new_started = 0
                            new_prev = 0
                            ans = (ans + dfs(pos + 1, new_prev, new_tight, new_started)) % MOD
                        else:
                            new_started = 1
                            new_prev = d
                            ans = (ans + dfs(pos + 1, new_prev, new_tight, new_started)) % MOD
                    else:
                        if d >= prev:
                            new_started = 1
                            new_prev = d
                            ans = (ans + dfs(pos + 1, new_prev, new_tight, new_started)) % MOD
                memo[key] = ans
                return ans

            return dfs(0, 0, 1, 0)

        r_num = int(r)
        right_count = count_up_to(to_base_b(r_num, b), b)
        l_num = int(l) - 1
        left_count = count_up_to(to_base_b(l_num, b), b)
        return (right_count - left_count + MOD) % MOD

# @lc code=end