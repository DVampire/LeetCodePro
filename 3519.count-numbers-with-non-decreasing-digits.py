#
# @lc app=leetcode id=3519 lang=python3
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
from functools import lru_cache

MOD = 10**9 + 7

class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        def dec_one(s: str) -> str:
            # assumes s represents an integer >= 0
            if s == "0":
                return "0"
            a = list(s)
            i = len(a) - 1
            while i >= 0 and a[i] == '0':
                a[i] = '9'
                i -= 1
            if i >= 0:
                a[i] = chr(ord(a[i]) - 1)
            # strip leading zeros
            res = ''.join(a).lstrip('0')
            return res if res else "0"

        def divmod_dec_str(num: str, d: int):
            # returns (quotient_str, remainder_int)
            rem = 0
            out = []
            for ch in num:
                rem = rem * 10 + (ord(ch) - 48)
                q = rem // d
                rem %= d
                out.append(chr(q + 48))
            qstr = ''.join(out).lstrip('0')
            return (qstr if qstr else "0", rem)

        def dec_to_base_digits(num: str, base: int):
            if num == "0":
                return [0]
            digits = []
            cur = num
            while cur != "0":
                cur, rem = divmod_dec_str(cur, base)
                digits.append(rem)
            digits.reverse()
            return digits

        def count_leq(x_dec: str) -> int:
            digits = dec_to_base_digits(x_dec, b)
            n = len(digits)

            @lru_cache(None)
            def dfs(i: int, prev: int, tight: int, started: int) -> int:
                if i == n:
                    return 1  # counts 0 if never started

                lim = digits[i] if tight else (b - 1)
                ans = 0
                for dgt in range(lim + 1):
                    ntight = 1 if (tight and dgt == lim) else 0
                    if started == 0 and dgt == 0:
                        ans += dfs(i + 1, 0, ntight, 0)
                    else:
                        if started == 0:
                            ans += dfs(i + 1, dgt, ntight, 1)
                        else:
                            if dgt >= prev:
                                ans += dfs(i + 1, dgt, ntight, 1)
                return ans % MOD

            return dfs(0, 0, 1, 0)

        l_minus_1 = dec_one(l)
        res = (count_leq(r) - count_leq(l_minus_1)) % MOD
        return res
# @lc code=end
