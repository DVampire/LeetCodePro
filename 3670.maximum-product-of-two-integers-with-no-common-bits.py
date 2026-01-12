#
# @lc app=leetcode id=3670 lang=python3
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        mask_to_max = {}
        for n in nums:
            if n not in mask_to_max or n > mask_to_max[n]:
                mask_to_max[n] = n
        
        unique_masks = list(mask_to_max.keys())
        ans = 0
        n_unique = len(unique_masks)
        
        # Sort masks by value descending to potentially prune or find larger products faster
        unique_masks.sort(reverse=True)
        
        for i in range(n_unique):
            m1 = unique_masks[i]
            v1 = mask_to_max[m1]
            # Optimization: if v1 * largest possible second value is less than current ans, skip
            if v1 * unique_masks[0] <= ans:
                continue
            for j in range(i + 1, n_unique):
                m2 = unique_masks[j]
                if (m1 & m2) == 0:
                    ans = max(ans, v1 * mask_to_max[m2])
        
        return ans
# @lc code=end