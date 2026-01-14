#
# @lc app=leetcode id=3677 lang=python3
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution:
    def countBinaryPalindromes(self, n: int) -> int:
        if n == 0:
            return 1
        
        bin_n = bin(n)[2:]
        L = len(bin_n)
        
        count = 1  # Count for "0"
        
        # Count all palindromes with length < L
        for length in range(1, L):
            if length == 1:
                count += 1  # Only "1"
            else:
                num_free_bits = (length + 1) // 2 - 1
                count += 2 ** num_free_bits
        
        # Count palindromes with length == L
        num_free_bits = (L + 1) // 2 - 1
        
        for i in range(2 ** num_free_bits):
            # Construct the palindrome
            if num_free_bits > 0:
                free_bits = bin(i)[2:].zfill(num_free_bits)
            else:
                free_bits = ""
            first_half = '1' + free_bits
            
            if L % 2 == 1:
                # Odd length
                palindrome = first_half + first_half[:-1][::-1]
            else:
                # Even length
                palindrome = first_half + first_half[::-1]
            
            palindrome_val = int(palindrome, 2)
            if palindrome_val <= n:
                count += 1
            else:
                break  # All subsequent palindromes will be > n
        
        return count
# @lc code=end