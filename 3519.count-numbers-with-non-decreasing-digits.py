#
# @lc app=leetcode id=3519 lang=python3
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
import sys

# Increase recursion depth for deep DP trees if necessary
sys.setrecursionlimit(2000)

class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10**9 + 7

        def get_base_b_digits(n_str, b):
            # Convert base-10 string to integer
            n = int(n_str)
            if n == 0:
                return [0]
            
            digits = []
            while n > 0:
                digits.append(n % b)
                n //= b
            return digits[::-1]

        def solve(digits):
            n = len(digits)
            memo = {}

            def dp(index, prev_digit, is_less, is_started):
                state = (index, prev_digit, is_less, is_started)
                if state in memo:
                    return memo[state]
                
                if index == n:
                    return 1 # Found one valid number
                
                res = 0
                limit = digits[index] if not is_less else b - 1
                
                # Determine the range of digits we can place
                # If not started, we can place 0 (which keeps it not started) 
                # or 1..limit (which starts it).
                # If started, we must place digit >= prev_digit.
                
                start = 0
                end = limit
                
                for d in range(start, end + 1):
                    if not is_started:
                        if d == 0:
                            # Still not started, effectively skipping this position (leading zero)
                            # However, we must be careful. The DP structure generally builds a number of length `n`.
                            # If we place a 0 here and remain !is_started, we are effectively building a number with fewer digits.
                            # But wait, does this specific DP structure count 0? 
                            # If we reach index == n and !is_started, we formed the number 0.
                            # The range is usually inclusive. If the input number is 5, we count 0, 1, 2, 3, 4, 5.
                            # Let's assume we count 0 as valid if it's non-decreasing (0 is trivially non-decreasing).
                            # But if the actual number we are counting <= N is 0, is_started will be false until end.
                            
                            # Special case: If we are at the last position and haven't started, placing 0 makes the number 0.
                            # Usually "leading zeros" logic is used to count numbers with fewer digits.
                            # If we place 0 and don't start, we move to next index.
                            
                            new_is_less = is_less or (d < limit)
                            res = (res + dp(index + 1, 0, new_is_less, False)) % MOD
                        else:
                            # Start the number. Since it's the first digit, constraint is just d > 0.
                            new_is_less = is_less or (d < limit)
                            res = (res + dp(index + 1, d, new_is_less, True)) % MOD
                    else:
                        # Already started, must be >= prev_digit
                        if d >= prev_digit:
                            new_is_less = is_less or (d < limit)
                            res = (res + dp(index + 1, d, new_is_less, True)) % MOD
                
                memo[state] = res
                return res

            return dp(0, 0, False, False)

        # Convert l and r to base b digits
        # We need count(r) - count(l-1)
        
        # Helper to handle the subtraction logic for l-1
        def count_le(n_str):
            digits = get_base_b_digits(n_str, b)
            # The DP counts numbers in [0, n_str].
            # 0 is always non-decreasing (single digit).
            return solve(digits)

        ans_r = count_le(r)
        
        # Calculate l-1 string
        l_int = int(l)
        ans_l_minus_1 = 0
        if l_int > 0:
            ans_l_minus_1 = count_le(str(l_int - 1))
            
        return (ans_r - ans_l_minus_1 + MOD) % MOD

# @lc code=end