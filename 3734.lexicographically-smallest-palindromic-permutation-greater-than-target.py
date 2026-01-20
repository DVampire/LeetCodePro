#
# @lc app=leetcode id=3734 lang=python3
#
# [3734] Lexicographically Smallest Palindromic Permutation Greater Than Target
#

# @lc code=start
from collections import Counter

class Solution:
    def lexPalindromicPermutation(self, s: str, target: str) -> str:
        n = len(s)
        freq = Counter(s)
        num_odd = sum(v % 2 for v in freq.values())
        if num_odd != n % 2:
            return ""
        
        m = n // 2
        num_pair = Counter({c: freq[c] // 2 for c in freq})
        
        odd_char = None
        if n % 2 == 1:
            for c in 'abcdefghijklmnopqrstuvwxyz':
                if freq[c] % 2 == 1:
                    odd_char = c
                    break
        
        T_left = target[:m]
        
        # Check equal case
        left_count = Counter(T_left)
        if left_count == num_pair:
            if n % 2 == 0:
                p_equal = T_left + T_left[::-1]
            else:
                p_equal = T_left + odd_char + T_left[::-1]
            if p_equal > target:
                return p_equal
        
        # Compute lex next greater LEFT > T_left
        def compute_next(U: str, counts: Counter, length: int) -> str | None:
            for k in range(length):
                pref = U[:k]
                pref_c = Counter(pref)
                if any(pref_c[c] > counts[c] for c in pref_c):
                    continue
                temp_rem = counts - pref_c
                ch = U[k]
                found_c = None
                for i in range(ord(ch) + 1, ord('z') + 1):
                    cc = chr(i)
                    if temp_rem[cc] > 0:
                        found_c = cc
                        break
                if found_c is None:
                    continue
                # Build res
                res = list(pref) + [found_c]
                temp_rem[found_c] -= 1
                # Fill remaining smallest
                for ccc in 'abcdefghijklmnopqrstuvwxyz':
                    for _ in range(temp_rem[ccc]):
                        res.append(ccc)
                return ''.join(res)
            return None
        
        next_left = compute_next(T_left, num_pair, m)
        if next_left is not None:
            if n % 2 == 0:
                return next_left + next_left[::-1]
            else:
                return next_left + odd_char + next_left[::-1]
        
        return ""

# @lc code=end