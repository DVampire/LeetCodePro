#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
from bisect import bisect_right

class Solution:
    _specials = None

    @staticmethod
    def _generate_all_special_palindromes(max_len: int = 17):
        res = []

        # digits are 1..9, represented by bit positions 0..8
        for mask in range(1, 1 << 9):
            digits = []
            total_len = 0
            odd_digits = 0
            odd_center = 0

            for i in range(9):
                if (mask >> i) & 1:
                    d = i + 1
                    digits.append(d)
                    total_len += d
                    if d % 2 == 1:
                        odd_digits += 1
                        odd_center = d

            if total_len > max_len:
                continue
            if odd_digits > 1:
                continue

            # Determine center
            if total_len % 2 == 0:
                if odd_digits != 0:
                    continue
                center = ""
            else:
                if odd_digits != 1:
                    continue
                center = str(odd_center)

            half_len = total_len // 2
            counts_left = [0] * 10
            for d in digits:
                counts_left[d] = d // 2

            left_chars = []

            def dfs(pos: int):
                if pos == half_len:
                    left = "".join(left_chars)
                    pal = left + center + left[::-1]
                    res.append(int(pal))
                    return

                for d in range(1, 10):
                    if counts_left[d] > 0:
                        counts_left[d] -= 1
                        left_chars.append(str(d))
                        dfs(pos + 1)
                        left_chars.pop()
                        counts_left[d] += 1

            dfs(0)

        res.sort()
        return res

    def specialPalindrome(self, n: int) -> int:
        if Solution._specials is None:
            # For n <= 1e15, length<=17 guarantees an answer.
            Solution._specials = Solution._generate_all_special_palindromes(17)

        idx = bisect_right(Solution._specials, n)
        return Solution._specials[idx]
# @lc code=end
