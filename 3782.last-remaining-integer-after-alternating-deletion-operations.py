#
# @lc app=leetcode id=3782 lang=python3
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#

# @lc code=start
class Solution:
    def lastInteger(self, n: int) -> int:
        head = 1
        step = 1
        remaining = n
        left = True
        
        while remaining > 1:
            # When going from right and count is even, first element is deleted
            if not left and remaining % 2 == 0:
                head += step
            
            step *= 2
            remaining = (remaining + 1) // 2
            left = not left
        
        return head
# @lc code=end