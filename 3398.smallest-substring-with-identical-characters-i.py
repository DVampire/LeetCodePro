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
            count = 1
            for i in range(1, n):
                if s[i] == s[i-1]:
                    count += 1
                else:
                    segments.append(count)
                    count = 1
            segments.append(count)
            
        def check(k: int) -> bool:
            if k == 1:
                # Check alternating patterns: "0101..." and "1010..."
                cost0 = 0
                cost1 = 0
                for i in range(n):
                    # Target for pattern starting with '0'
                    t0 = '0' if i % 2 == 0 else '1'
                    if s[i] != t0:
                        cost0 += 1
                    # Target for pattern starting with '1'
                    t1 = '1' if i % 2 == 0 else '0'
                    if s[i] != t1:
                        cost1 += 1
                return min(cost0, cost1) <= numOps
            else:
                # Greedy strategy for k > 1
                total_ops = 0
                for length in segments:
                    total_ops += length // (k + 1)
                return total_ops <= numOps

        # Binary search for the minimum k
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