#
# @lc app=leetcode id=3785 lang=python3
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#
# @lc code=start
class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        from collections import Counter
        
        n = len(nums)
        
        num_count = Counter(nums)
        forbidden_count = Counter(forbidden)
        bad_count = Counter()
        
        total_bad = 0
        for i in range(n):
            if nums[i] == forbidden[i]:
                total_bad += 1
                bad_count[nums[i]] += 1
        
        if total_bad == 0:
            return 0
        
        max_count = max(bad_count.values())
        
        def compatible_good_count(v):
            return n - total_bad - num_count[v] - forbidden_count[v] + 2 * bad_count[v]
        
        if 2 * max_count <= total_bad:  # Balanced
            if total_bad % 2 == 1:
                if not any(compatible_good_count(v) >= 1 for v in bad_count):
                    return -1
        else:  # Unbalanced
            dominant_value = max(bad_count, key=bad_count.get)
            unpaired = 2 * max_count - total_bad
            if compatible_good_count(dominant_value) < unpaired:
                return -1
        
        return max((total_bad + 1) // 2, max_count)
# @lc code=end