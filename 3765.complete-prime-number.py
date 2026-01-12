#
# @lc app=leetcode id=3765 lang=python3
#
# [3765] Complete Prime Number
#

# @lc code=start
class Solution:
    def completePrime(self, num: int) -> bool:
        def is_prime(n: int) -> bool:
            """Check if a number is prime using trial division up to sqrt(n)."""
            if n < 2:
                return False
            if n == 2 or n == 3:
                return True
            if n % 2 == 0 or n % 3 == 0:
                return False
            i = 5
            while i * i <= n:
                if n % i == 0 or n % (i + 2) == 0:
                    return False
                i += 6
            return True
        
        s = str(num)
        length = len(s)
        
        # Check all prefixes and all suffixes
        for i in range(1, length + 1):
            # Prefix is the first i digits
            prefix = int(s[:i])
            if not is_prime(prefix):
                return False
            
            # Suffix is the last i digits
            suffix = int(s[length - i:])
            if not is_prime(suffix):
                return False
                
        return True
# @lc code=end