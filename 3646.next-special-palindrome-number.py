#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
from itertools import permutations
import bisect

class Solution:
    def specialPalindrome(self, n: int) -> int:
        all_palindromes = set()
        
        def generate_subsets(max_sum):
            result = []
            def backtrack(start, current, total, odd):
                if odd > 1:
                    return
                if current:
                    result.append(tuple(current))
                for d in range(start, 10):
                    if total + d > max_sum:
                        break
                    current.append(d)
                    backtrack(d + 1, current, total + d, odd + (d % 2))
                    current.pop()
            backtrack(1, [], 0, 0)
            return result
        
        for subset in generate_subsets(22):
            middle = next((d for d in subset if d % 2 == 1), None)
            
            half = []
            for d in subset:
                half.extend([d] * (d // 2))
            
            if not half:
                all_palindromes.add(middle)
            else:
                for perm in set(permutations(half)):
                    s1 = ''.join(map(str, perm))
                    if middle is not None:
                        p = s1 + str(middle) + s1[::-1]
                    else:
                        p = s1 + s1[::-1]
                    all_palindromes.add(int(p))
        
        sorted_palindromes = sorted(all_palindromes)
        return sorted_palindromes[bisect.bisect_right(sorted_palindromes, n)]
# @lc code=end