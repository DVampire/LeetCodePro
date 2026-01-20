#
# @lc app=leetcode id=3398 lang=python3
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        def check(length):
            if length == 1:
                # Check cost to make 010101...
                cost1 = 0
                for i in range(n):
                    if i % 2 == 0:
                        if s[i] != '0': cost1 += 1
                    else:
                        if s[i] != '1': cost1 += 1
                
                # Check cost to make 101010...
                cost2 = 0
                for i in range(n):
                    if i % 2 == 0:
                        if s[i] != '1': cost2 += 1
                    else:
                        if s[i] != '0': cost2 += 1
                
                return min(cost1, cost2) <= numOps
            
            # For length >= 2, we calculate flips needed for each consecutive block
            # A block of size L needs L // (length + 1) flips to ensure no sub-block > length
            ops_needed = 0
            i = 0
            while i < n:
                j = i
                while j < n and s[j] == s[i]:
                    j += 1
                
                run_length = j - i
                ops_needed += run_length // (length + 1)
                i = j
            
            return ops_needed <= numOps

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