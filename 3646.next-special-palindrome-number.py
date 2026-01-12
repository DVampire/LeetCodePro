#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
from itertools import permutations

class Solution:
    def specialPalindrome(self, n: int) -> int:
        str_n = str(n)
        len_n = len(str_n)
        
        even_digits = [2, 4, 6, 8]
        odd_digits = [1, 3, 5, 7, 9]
        
        def get_valid_sets(L):
            valid_sets = []
            if L % 2 == 0:
                # L is even, only even digits allowed
                def find_even_subsets(index, current_sum, current_set):
                    if current_sum == L:
                        valid_sets.append(list(current_set))
                        return
                    if index == len(even_digits) or current_sum > L:
                        return
                    # Include even_digits[index]
                    current_set.append(even_digits[index])
                    find_even_subsets(index + 1, current_sum + even_digits[index], current_set)
                    current_set.pop()
                    # Exclude
                    find_even_subsets(index + 1, current_sum, current_set)
                
                find_even_subsets(0, 0, [])
            else:
                # L is odd, exactly one odd digit allowed
                for o in odd_digits:
                    target = L - o
                    if target < 0: continue
                    
                    def find_even_subsets_for_odd(index, current_sum, current_set):
                        if current_sum == target:
                            valid_sets.append(list(current_set) + [o])
                            return
                        if index == len(even_digits) or current_sum > target:
                            return
                        # Include
                        current_set.append(even_digits[index])
                        find_even_subsets_for_odd(index + 1, current_sum + even_digits[index], current_set)
                        current_set.pop()
                        # Exclude
                        find_even_subsets_for_odd(index + 1, current_sum, current_set)
                    
                    find_even_subsets_for_odd(0, 0, [])
            return valid_sets

        for L in range(len_n, 46):
            sets = get_valid_sets(L)
            candidates = []
            for S in sets:
                if L % 2 == 0:
                    counts = {k: k // 2 for k in S}
                    half_L = L // 2
                    elements = []
                    for k, count in counts.items():
                        elements.extend([str(k)] * count)
                    
                    seen_prefixes = set()
                    for p in permutations(elements):
                        prefix = "".join(p)
                        if prefix in seen_prefixes: continue
                        seen_prefixes.add(prefix)
                        pal = prefix + prefix[::-1]
                        val = int(pal)
                        if val > n:
                            candidates.append(val)
                else:
                    o = [k for k in S if k % 2 == 1][0]
                    counts = {k: k // 2 for k in S if k != o}
                    counts[o] = (o - 1) // 2
                    half_L = (L - 1) // 2
                    elements = []
                    for k, count in counts.items():
                        elements.extend([str(k)] * count)
                    
                    seen_prefixes = set()
                    for p in permutations(elements):
                        prefix = "".join(p)
                        if prefix in seen_prefixes: continue
                        seen_prefixes.add(prefix)
                        pal = prefix + str(o) + prefix[::-1]
                        val = int(pal)
                        if val > n:
                            candidates.append(val)
            
            if candidates:
                return min(candidates)
        
        return -1
# @lc code=end