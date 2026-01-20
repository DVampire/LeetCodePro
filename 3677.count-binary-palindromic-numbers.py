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
        
        s = bin(n)[2:]
        length = len(s)
        ans = 1  # Start with 1 because 0 is always a binary palindrome
        
        # 1. Count all palindromes with length < length of n
        for l in range(1, length):
            # The first bit must be 1. The palindrome is determined by the first ceil(l/2) bits.
            # Since the first bit is fixed to 1, we have ceil(l/2) - 1 bits to choose freely.
            count = 1 << ((l + 1) // 2 - 1)
            ans += count
            
        # 2. Count palindromes with length == length of n
        # Number of bits determining the palindrome
        half_len = (length + 1) // 2
        
        # The prefix of n that determines the palindrome shape
        prefix_str = s[:half_len]
        prefix_val = int(prefix_str, 2)
        
        # The smallest valid prefix for this length starts with 1 followed by zeros
        # It corresponds to 1 << (half_len - 1)
        min_prefix_val = 1 << (half_len - 1)
        
        # All prefixes from min_prefix_val to prefix_val - 1 form valid palindromes < n
        if prefix_val > min_prefix_val:
            ans += (prefix_val - min_prefix_val)
            
        # 3. Check the palindrome formed by prefix_str itself
        # Construct the palindrome
        left_part = prefix_str
        if length % 2 == 1:
            # Odd length: e.g., prefix "10", len 3 -> "10" + "1" = "101"
            right_part = left_part[:-1][::-1]
        else:
            # Even length: e.g., prefix "10", len 4 -> "10" + "01" = "1001"
            right_part = left_part[::-1]
            
        candidate_str = left_part + right_part
        candidate_val = int(candidate_str, 2)
        
        if candidate_val <= n:
            ans += 1
            
        return ans
# @lc code=end