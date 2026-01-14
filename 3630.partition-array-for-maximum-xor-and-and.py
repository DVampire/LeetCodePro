#
# @lc app=leetcode id=3630 lang=python3
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        n = len(nums)
        max_val = 0
        
        # Iterate through all 3^n partitions
        for partition in range(3 ** n):
            # Decode partition to assignment (0=A, 1=B, 2=C)
            assignment = []
            temp = partition
            for i in range(n):
                assignment.append(temp % 3)
                temp //= 3
            
            # Calculate XOR(A), AND(B), XOR(C)
            xor_a = 0
            and_b = 0
            first_b = True
            xor_c = 0
            
            for i in range(n):
                if assignment[i] == 0:  # A
                    xor_a ^= nums[i]
                elif assignment[i] == 1:  # B
                    if first_b:
                        and_b = nums[i]
                        first_b = False
                    else:
                        and_b &= nums[i]
                else:  # C
                    xor_c ^= nums[i]
            
            # Update maximum
            max_val = max(max_val, xor_a + and_b + xor_c)
        
        return max_val
# @lc code=end