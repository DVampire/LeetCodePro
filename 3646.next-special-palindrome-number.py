#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
from itertools import permutations, combinations

class Solution:
    def specialPalindrome(self, n: int) -> int:
        s_n = str(n)
        len_n = len(s_n)
        
        # We iterate through lengths starting from the length of n
        # Since n <= 10^15, reasonable upper bound for length is enough.
        # Max possible sum of unique digits 1-9 is 45, but we stop as soon as we find a solution.
        for length in range(len_n, 46):
            candidates = []
            
            # Find all subsets of digits {1..9} that sum to 'length'
            # and satisfy parity constraints.
            # Parity constraint: 
            #   If length is even, all digits in subset must be even.
            #   If length is odd, exactly one digit in subset must be odd.
            
            valid_subsets = []
            
            # Helper to find subsets
            def find_subsets(target, current_digits, index):
                if target == 0:
                    valid_subsets.append(list(current_digits))
                    return
                if target < 0 or index > 9:
                    return
                
                # Include index
                find_subsets(target - index, current_digits + [index], index + 1)
                # Exclude index
                find_subsets(target, current_digits, index + 1)

            find_subsets(length, [], 1)
            
            for subset in valid_subsets:
                # Check parity constraints
                odds = [d for d in subset if d % 2 != 0]
                evens = [d for d in subset if d % 2 == 0]
                
                mid_digit = -1
                half_digits = []
                
                if length % 2 == 0:
                    if len(odds) != 0:
                        continue
                    # All evens, form half digits
                    for d in subset:
                        half_digits.extend([str(d)] * (d // 2))
                else:
                    if len(odds) != 1:
                        continue
                    mid_digit = odds[0]
                    # Add half counts for all numbers (odd one loses 1 for middle)
                    for d in subset:
                        half_digits.extend([str(d)] * (d // 2))
                
                # If we are strictly above the original length, we just want the smallest number
                # formed by these digits. Sort half_digits to get smallest prefix.
                if length > len_n:
                    half_digits.sort()
                    half_s = "".join(half_digits)
                    if length % 2 == 0:
                        cand_str = half_s + half_s[::-1]
                    else:
                        cand_str = half_s + str(mid_digit) + half_s[::-1]
                    candidates.append(int(cand_str))
                else:
                    # Length matches n. We need to check permutations to find strictly greater
                    # Since max length is around 16, half length is ~8. 8! is small (40k).
                    # We can generate unique permutations.
                    unique_perms = sorted(list(set(permutations(half_digits))))
                    for p in unique_perms:
                        half_s = "".join(p)
                        if length % 2 == 0:
                            cand_str = half_s + half_s[::-1]
                        else:
                            cand_str = half_s + str(mid_digit) + half_s[::-1]
                        
                        val = int(cand_str)
                        if val > n:
                            candidates.append(val)
            
            if candidates:
                return min(candidates)
                
        return -1 # Should not reach here

# @lc code=end