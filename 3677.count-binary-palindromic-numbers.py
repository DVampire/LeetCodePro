#
# @lc app=leetcode id=3677 lang=python3
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution:
    def countBinaryPalindromes(self, n: int) -> int:
        # If n is 0, only 0 is palindrome
        if n == 0:
            return 1
        
        # Helper function to generate binary palindromes of given length
        def generate_palindromes(length):
            # length is the number of bits in the binary representation (without leading zeros)
            # For length 1: palindromes are "0" and "1" (but note: "0" is only for number 0, which we handle separately)
            # Actually we generate all binary strings of given length that are palindromes.
            # For odd length: half = (length + 1) // 2 bits for first half, then mirror excluding middle.
            # For even length: half = length // 2 bits for first half, then mirror.
            half = (length + 1) // 2
            res = []
            # The first bit must be 1 because binary representation has no leading zeros (except number 0).
            # So we iterate over all numbers from 2^(half-1) to 2^half - 1.
            start = 1 << (half - 1) if half > 0 else 0
            end = (1 << half) - 1
            for i in range(start, end + 1):
                # Build palindrome binary string
                if length % 2 == 0:
                    # Even: mirror whole half
                    first_half = bin(i)[2:].zfill(half)
                    full = first_half + first_half[::-1]
                else:
                    # Odd: mirror half excluding middle bit
                    first_half = bin(i)[2:].zfill(half)
                    full = first_half + first_half[-2::-1]   # exclude middle, i.e., reverse without last char
                res.append(int(full, 2))
            return res
        
        # Determine max length of binary representation of n
        max_len = n.bit_length()
        count = 1  # for number 0
        # For each length from 1 to max_len, generate palindromes and count those <= n
        for l in range(1, max_len + 1):
            pals = generate_palindromes(l)
            for p in pals:
                if p <= n:
                    count += 1
        return count
# @lc code=end