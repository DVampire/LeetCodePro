#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        def feasible(M):
            # Returns True if it's possible to achieve max run length <= M
            # using at most numOps operations.
            def calculate(start_char):
                edits = 0
                cur_char = start_char
                cur_len = 0
                for ch in s:
                    if cur_len == M:
                        # forced switch
                        new_char = '0' if cur_char == '1' else '1'
                        if new_char != ch:
                            edits += 1
                        cur_char = new_char
                        cur_len = 1
                    else:
                        # stay with current char
                        new_char = cur_char
                        if new_char != ch:
                            edits += 1
                        cur_len += 1
                return edits
            
            # Try both possible starting characters.
            return min(calculate('0'), calculate('1')) <= numOps
        
        # Binary search on answer.
        lo = 1
        hi = n
        while lo < hi:
            mid = lo + hi >> 1
            if feasible(mid):
                hi = mid
            else:
                lo = mid + 1
        return lo

# @lc code=end
