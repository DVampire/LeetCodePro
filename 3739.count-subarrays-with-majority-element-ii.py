#
# @lc app=leetcode id=3739 lang=python3
#
# [3739] Count Subarrays With Majority Element II
#

# @lc code=start
class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        # The prefix sums range from -n to n. 
        # We use an offset of n to map this range to 0 to 2n.
        offset = n
        freq = [0] * (2 * n + 1)
        
        ans = 0
        cur_P = 0 # Represents the current prefix sum P_k
        freq[cur_P + offset] = 1 # Initial prefix sum P_0 = 0
        smaller_counts = 0 # Number of previous prefix sums P_i < cur_P
        
        for x in nums:
            if x == target:
                # Prefix sum increases: P_{k+1} = P_k + 1
                # The number of i <= k such that P_i < P_{k+1} is:
                # count(P_i < P_k) + count(P_i == P_k)
                smaller_counts += freq[cur_P + offset]
                cur_P += 1
            else:
                # Prefix sum decreases: P_{k+1} = P_k - 1
                # The number of i <= k such that P_i < P_{k+1} is:
                # count(P_i < P_k) - count(P_i == P_k - 1)
                cur_P -= 1
                smaller_counts -= freq[cur_P + offset]
            
            # Add the number of valid starting indices i for the current end index k
            ans += smaller_counts
            # Update the frequency of the newly reached prefix sum
            freq[cur_P + offset] += 1
            
        return ans
# @lc code=end