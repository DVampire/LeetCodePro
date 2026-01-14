#
# @lc app=leetcode id=3765 lang=python3
#
# [3765] Complete Prime Number
#
# @lc code=start
class Solution:
    def completePrime(self, num: int) -> bool:
        def is_prime(n):
            if n < 2:
                return False
            if n == 2:
                return True
            if n % 2 == 0:
                return False
            for i in range(3, int(n**0.5) + 1, 2):
                if n % i == 0:
                    return False
            return True
        
        # Convert to string to get prefixes and suffixes
        num_str = str(num)
        
        # Check all prefixes
        for i in range(1, len(num_str) + 1):
            prefix = int(num_str[:i])
            if not is_prime(prefix):
                return False
        
        # Check all suffixes
        for i in range(len(num_str)):
            suffix = int(num_str[i:])
            if not is_prime(suffix):
                return False
        
        return True
# @lc code=end