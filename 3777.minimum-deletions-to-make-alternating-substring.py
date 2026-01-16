#
# @lc app=leetcode id=3777 lang=python3
#
# [3777] Minimum Deletions to Make Alternating Substring
#

from typing import List

# @lc code=start
class Solution:
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        # Convert string to mutable list
        arr = list(s)
        # Fenwick Tree implementation
        class BIT:
            def __init__(self, sz):
                self.n = sz
                self.tree = [0] * (sz + 5)
            def add(self, idx: int, delta: int):
                # idx is 1-indexed
                while idx <= self.n:
                    self.tree[idx] += delta
                    idx += idx & -idx
            def sum(self, idx: int) -> int:
                res = 0
                while idx > 0:
                    res += self.tree[idx]
                    idx -= idx & -idx
                return res
        
        # Initialize difference array and BIT
        # diff[i] indicates whether arr[i] != arr[i+1], stored at BIT index i+1
        # We'll maintain an explicit list diff for quick access
        diff = [0] * n
        bit = BIT(n + 5)
        for i in range(n - 1):
            if arr[i] != arr[i + 1]:
                diff[i] = 1
                bit.add(i + 1, 1)
        
        def toggle(ch):
            return 'B' if ch == 'A' else 'A'
        
        ans = []
        for q in queries:
            typ = q[0]
            if typ == 1:
                # flip operation
                j = q[1]
                # toggle character
                old_char = arr[j]
                new_char = toggle(old_char)
                arr[j] = new_char
                # update left pair if exists
                if j > 0:
                    idx_left = j - 1
                    new_val_left = int(arr[idx_left] != arr[j])   # arr[idx_left]!=new_char
                    old_val_left = diff[idx_left]
                    delta_left = new_val_left - old_val_left
                    if delta_left:
                        diff[idx_left] = new_val_left
                        bit.add(idx_left + 1, delta_left)
                # update right pair if exists
                if j < n - 1:
                    idx_right = j
                    new_val_right = int(arr[j] != arr[idx_right + 1])   # new_char!=arr[j+1]
                    old_val_right = diff[idx_right]
                    delta_right = new_val_right - old_val_right
                    if delta_right:
                        diff[idx_right] = new_val_right
                        bit.add(idx_right + 1, delta_right)
            else:
                # query operation type [2,l,r]
                l_val = q[1]
                r_val = q[2]
                sub_len = r_val - l_val + 1
                # Number of differences inside [l_val,r_val)
                # Using formula sum_{i=l}^{r-1} diff[i]
                # Equivalent to prefix_sum(r) - prefix_sum(l)
                # Because prefix_sum(x) sums diff[0..x-1]
                cnt_changes = bit.sum(r_val) - bit.sum(l_val)
                # Number of runs = cnt_changes + 1
                deletions_needed = sub_len - (cnt_changes + 1)
                ans.append(deletions_needed)
        return ans
# @lc code=end