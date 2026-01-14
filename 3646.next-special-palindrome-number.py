#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
class Solution:
    def specialPalindrome(self, n: int) -> int:
        special = []
        
        # Generate all subsets of digits 1-9
        for mask in range(1, 1 << 9):
            digits = []
            for d in range(1, 10):
                if mask & (1 << (d - 1)):
                    digits.append(d)
            
            # Check if valid (at most one odd digit)
            odd_count = sum(1 for d in digits if d % 2 == 1)
            if odd_count > 1:
                continue
            
            total_len = sum(digits)
            
            # Skip if too long
            if total_len > 18:
                continue
            
            # Generate the smallest palindrome
            counts = {d: d for d in digits}
            
            # Determine middle element
            middle = None
            for d in digits:
                if d % 2 == 1:
                    middle = d
                    counts[d] -= 1
                    break
            
            # Build the first half
            half_len = total_len // 2
            first_half = []
            
            for _ in range(half_len):
                for d in sorted(digits):
                    if counts[d] >= 2:
                        first_half.append(d)
                        counts[d] -= 2
                        break
            
            # Construct the palindrome
            if middle is not None:
                palin = first_half + [middle] + first_half[::-1]
            else:
                palin = first_half + first_half[::-1]
            
            num = int(''.join(map(str, palin)))
            if num <= 10**18:
                special.append(num)
        
        special.sort()
        
        # Find the next special number after n
        for num in special:
            if num > n:
                return num
        
        return -1
# @lc code=end