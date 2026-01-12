#
# @lc app=leetcode id=3782 lang=python3
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#

# @lc code=start
class Solution:
    def lastInteger(self, n: int) -> int:
        start = 1
        step = 1
        count = n
        left = True
        
        while count > 1:
            if left:
                # Operation 1: Start from left, delete every second.
                # The first element (index 0) is always kept.
                pass
            else:
                # Operation 2: Start from right, delete every second.
                # If count is even (e.g., 4), elements are indices 3, 2, 1, 0 from right.
                # 2nd (index 2) and 4th (index 0) are deleted. New start is index 1.
                # If count is odd (e.g., 5), elements are indices 4, 3, 2, 1, 0 from right.
                # 2nd (index 3) and 4th (index 1) are deleted. New start is index 0.
                if count % 2 == 0:
                    start += step
            
            # Update count and step for the next iteration
            count = (count + 1) // 2
            step *= 2
            left = not left
            
        return start
# @lc code=end