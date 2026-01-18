#
# @lc app=leetcode id=3398 lang=python3
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        # Pre-calculate segment lengths for k > 1 logic
        segments = []
        if n > 0:
            curr_len = 1
            for i in range(1, n):
                if s[i] == s[i-1]:
                    curr_len += 1
                else:
                    segments.append(curr_len)
                    curr_len = 1
            segments.append(curr_len)

        def check(k: int) -> bool:
            if k == 1:
                # Check alternating patterns 0101... and 1010...
                count1 = 0 # pattern starts with 0
                count2 = 0 # pattern starts with 1
                for i in range(n):
                    expected1 = '0' if i % 2 == 0 else '1'
                    if s[i] != expected1:
                        count1 += 1
                    
                    expected2 = '1' if i % 2 == 0 else '0'
                    if s[i] != expected2:
                        count2 += 1
                return min(count1, count2) <= numOps
            else:
                # Check segments of identical characters
                total_flips = 0
                for length in segments:
                    total_flips += length // (k + 1)
                return total_flips <= numOps

        # Binary search for the minimum length k
        low = 1
        high = n
        ans = n
        
        while low <= high:
            mid = (low + high) // 2
            if check(mid):
                ans = mid
                high = mid - 1
            else:
                low = mid + 1
                
        return ans
# @lc code=end