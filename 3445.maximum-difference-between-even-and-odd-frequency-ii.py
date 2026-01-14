#
# @lc app=leetcode id=3445 lang=python3
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        n = len(s)
        ans = float('-inf')
        
        for a in '01234':
            for b in '01234':
                if a == b:
                    continue
                
                # Precompute prefix sums
                prefix_a = [0] * (n + 1)
                prefix_b = [0] * (n + 1)
                for i in range(n):
                    prefix_a[i+1] = prefix_a[i] + (1 if s[i] == a else 0)
                    prefix_b[i+1] = prefix_b[i] + (1 if s[i] == b else 0)
                
                INF = float('inf')
                # min_data[(pa, pb)] = [min1, pb1, min2]
                # min1: minimum diff, pb1: prefix_b value achieving min1
                # min2: minimum diff among positions with prefix_b != pb1
                min_data = {(pa, pb): [INF, -1, INF] for pa in range(2) for pb in range(2)}
                
                for r in range(k, n + 1):
                    # Make position l = r - k eligible
                    l = r - k
                    pa_l = prefix_a[l] % 2
                    pb_l = prefix_b[l] % 2
                    diff_l = prefix_a[l] - prefix_b[l]
                    pb_val_l = prefix_b[l]
                    state = (pa_l, pb_l)
                    
                    # Update min_data[state]
                    data = min_data[state]
                    if diff_l < data[0]:
                        if pb_val_l != data[1]:
                            data[2] = data[0]
                        data[0], data[1] = diff_l, pb_val_l
                    elif pb_val_l != data[1]:
                        data[2] = min(data[2], diff_l)
                    
                    # Query at r
                    pa_r = prefix_a[r] % 2
                    pb_r = prefix_b[r] % 2
                    target_state = (1 - pa_r, pb_r)
                    target_data = min_data[target_state]
                    
                    diff_r = prefix_a[r] - prefix_b[r]
                    pb_val_r = prefix_b[r]
                    
                    if pb_val_r != target_data[1]:
                        if target_data[0] != INF:
                            ans = max(ans, diff_r - target_data[0])
                    else:
                        if target_data[2] != INF:
                            ans = max(ans, diff_r - target_data[2])
        
        return ans
# @lc code=end