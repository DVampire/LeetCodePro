#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        def check(limit):
            if limit == 1:
                # Special case for limit = 1: target is alternating string
                # Pattern 1: 010101...
                # Pattern 2: 101010...
                ops1 = 0
                ops2 = 0
                for i, char in enumerate(s):
                    # Expected for pattern 1: '0' if i even, '1' if i odd
                    expected1 = '0' if i % 2 == 0 else '1'
                    if char != expected1:
                        ops1 += 1
                    
                    # Expected for pattern 2: '1' if i even, '0' if i odd
                    expected2 = '1' if i % 2 == 0 else '0'
                    if char != expected2:
                        ops2 += 1
                return min(ops1, ops2) <= numOps
            
            # General case for limit > 1
            ops = 0
            current_len = 0
            last_char = ''
            
            for i, char in enumerate(s):
                if char == last_char:
                    current_len += 1
                else:
                    # Process the previous segment
                    if current_len > 0:
                        ops += current_len // (limit + 1)
                    current_len = 1
                    last_char = char
            
            # Process the last segment
            if current_len > 0:
                ops += current_len // (limit + 1)
                
            return ops <= numOps

        left, right = 1, n
        ans = n
        
        while left <= right:
            mid = (left + right) // 2
            if check(mid):
                ans = mid
                right = mid - 1
            else:
                left = mid + 1
                
        return ans

# @lc code=end