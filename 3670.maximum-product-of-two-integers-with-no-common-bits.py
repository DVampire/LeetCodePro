#
# @lc app=leetcode id=3670 lang=python3
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

from typing import List

# @lc code=start
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        """
        Find two distinct indices i,j such that nums[i] & nums[j]==0,
        maximizing product nums[i]*nums[j].
        """
        n = len(nums)
        if n < 2:
            return 0
        
        # Determine required number of bits
        max_num = max(nums)
        L = max_num.bit_length()
        total_masks = 1 << L          # size = pow(2,L)
        
        # Store maximum number per exact mask
        max_val = [0] * total_masks
        present_masks = []          
        
        for x in nums:
            # x itself serves as its unique bit pattern
            idx = x
            
            # Record first occurrence of this exact pattern
            if idx < total_masks:
                if not max_val[idx]:
                    present_masks.append(idx)
                
                # Store x as representative.
                # Since idx uniquely identifies x among positive ints,
                # storing x itself suffices.
                max_val[idx] = x
        
        # Initialize DP array for Sum Over Subsets.
        # After DP processing,
        #   dp[mask]=max{max_val[s] | s subset-of mask}
        dp = list(max_val)
        
        # Standard SOS DP for taking maximum over subsets.
        for i in range(L):
            step = 1 << i
            for mask in range(total_masks):
                if mask & step:
                    other = mask ^ step
                    cand = dp[other]
                    
                    # Update current entry using entry without this bit.
                    if cand > dp[mask]:
                        dp[mask] = cand

        ans = 0
        full_mask = total_masks - 1   # All lower L bits are ones.

        for cur_mask in present_masks:
            val_cur = cur_mask          
            
            # Complement w.r.t lower L bits.
            comp = (~cur_mask) & full_mask
            best_partner = dp[comp]

            # Ensure partner exists and yields valid product.
            if best_partner:
                prod = val_cur * best_partner
                ans = prod if prod > ans else ans

        return ans
# @lc code=end