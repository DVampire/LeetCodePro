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
        counts = Counter(s)
        odd_chars = [char for char, count in counts.items() if count % 2 != 0]
        
        if len(odd_chars) > 1:
            return ""
            
        mid_char = odd_chars[0] if odd_chars else ""
        half_chars = []
        for char, count in sorted(counts.items()):
            half_chars.extend([char] * (count // 2))
            
        half_len = n // 2
        
        def build_palindrome(half):
            res = list(half)
            if n % 2 != 0:
                res.append(mid_char)
            res.extend(reversed(half))
            return "".join(res)

        # Try to see if the target itself (or the smallest palindrome >= target) works
        # We iterate from the middle to the front to find the first point of divergence
        for i in range(half_len, -1, -1):
            # Try to increment at index i
            prefix = target[:i]
            current_counts = Counter(half_chars)
            possible = True
            for char in prefix:
                if current_counts[char] > 0:
                    current_counts[char] -= 1
                else:
                    possible = False
                    break
            if not possible: continue
            
            # Find a character at index i that is > target[i]
            target_char = target[i] if i < half_len else ""
            
            # Special case: if i == half_len, we only check if the current prefix + mid + rev(prefix) > target
            if i == half_len:
                candidate_half = "".join(list(target[:half_len]))
                # Re-verify if target[:half_len] is constructible from half_chars
                if Counter(candidate_half) == Counter(half_chars):
                    p = build_palindrome(candidate_half)
                    if p > target:
                        return p
                continue

            for char_code in range(ord(target_char) + 1, ord('z') + 1):
                char = chr(char_code)
                if current_counts[char] > 0:
                    # Found the smallest char to make it strictly greater
                    temp_half = list(prefix) + [char]
                    temp_counts = Counter(current_counts)
                    temp_counts[char] -= 1
                    # Fill the rest with smallest available
                    for c in sorted(temp_counts.keys()):
                        temp_half.extend([c] * temp_counts[c])
                    
                    return build_palindrome("".join(temp_half))
        
        return ""
# @lc code=end