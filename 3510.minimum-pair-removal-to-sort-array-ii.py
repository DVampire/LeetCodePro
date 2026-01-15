#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
from sortedcontainers import SortedList

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return 0
        
        # Doubly linked list using arrays
        prev = [i - 1 for i in range(n)]
        nxt = [i + 1 for i in range(n)]
        val = list(nums)
        deleted = [False] * n
        
        # Count bad pairs (where left > right)
        bad_count = sum(1 for i in range(n - 1) if val[i] > val[i + 1])
        if bad_count == 0:
            return 0
        
        # SortedList of (sum, left_index) for efficient min-sum retrieval
        pairs = SortedList()
        for i in range(n - 1):
            pairs.add((val[i] + val[i + 1], i))
        
        operations = 0
        
        while bad_count > 0:
            # Get minimum sum pair with lazy deletion
            while pairs:
                min_sum, left_idx = pairs[0]
                right_idx = nxt[left_idx]
                if (not deleted[left_idx] and 
                    right_idx < n and 
                    not deleted[right_idx] and 
                    val[left_idx] + val[right_idx] == min_sum):
                    break
                pairs.pop(0)
            
            # Remove the valid pair
            pairs.pop(0)
            
            right_idx = nxt[left_idx]
            new_val = val[left_idx] + val[right_idx]
            
            prev_left = prev[left_idx]
            next_right = nxt[right_idx]
            
            # Update bad_count and pairs for (prev_left, left_idx)
            if prev_left >= 0:
                if val[prev_left] > val[left_idx]:
                    bad_count -= 1
                if val[prev_left] > new_val:
                    bad_count += 1
                pairs.discard((val[prev_left] + val[left_idx], prev_left))
                pairs.add((val[prev_left] + new_val, prev_left))
            
            # Update bad_count for merged pair
            if val[left_idx] > val[right_idx]:
                bad_count -= 1
            
            # Update bad_count and pairs for (right_idx, next_right)
            if next_right < n:
                if val[right_idx] > val[next_right]:
                    bad_count -= 1
                if new_val > val[next_right]:
                    bad_count += 1
                pairs.discard((val[right_idx] + val[next_right], right_idx))
                pairs.add((new_val + val[next_right], left_idx))
            
            # Update linked list
            val[left_idx] = new_val
            deleted[right_idx] = True
            nxt[left_idx] = next_right
            if next_right < n:
                prev[next_right] = left_idx
            
            operations += 1
        
        return operations
# @lc code=end