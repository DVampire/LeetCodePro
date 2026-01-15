#
# @lc app=leetcode id=3721 lang=python3
#
# [3721] Longest Balanced Subarray II
#

# @lc code=start
from typing import List

class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0
        
        # Segment tree with lazy propagation for range add
        # Store both min and max for efficient zero-finding
        tree_min = [0] * (4 * n)
        tree_max = [0] * (4 * n)
        lazy = [0] * (4 * n)
        
        def push_down(node):
            if lazy[node] != 0:
                for child in [2*node, 2*node+1]:
                    tree_min[child] += lazy[node]
                    tree_max[child] += lazy[node]
                    lazy[child] += lazy[node]
                lazy[node] = 0
        
        def range_add(node, start, end, l, r, val):
            if r < start or l > end:
                return
            if l <= start and end <= r:
                tree_min[node] += val
                tree_max[node] += val
                lazy[node] += val
                return
            push_down(node)
            mid = (start + end) // 2
            range_add(2*node, start, mid, l, r, val)
            range_add(2*node+1, mid+1, end, l, r, val)
            tree_min[node] = min(tree_min[2*node], tree_min[2*node+1])
            tree_max[node] = max(tree_max[2*node], tree_max[2*node+1])
        
        def find_leftmost_zero(node, start, end, ql, qr):
            if qr < start or ql > end:
                return -1
            if tree_max[node] < 0 or tree_min[node] > 0:
                return -1
            if start == end:
                return start if tree_min[node] == 0 else -1
            push_down(node)
            mid = (start + end) // 2
            res = find_leftmost_zero(2*node, start, mid, ql, qr)
            if res != -1:
                return res
            return find_leftmost_zero(2*node+1, mid+1, end, ql, qr)
        
        last_occurrence = {}
        result = 0
        
        for r in range(n):
            val = nums[r]
            parity = 1 if val % 2 == 0 else -1
            last_occ = last_occurrence.get(val, -1)
            
            range_add(1, 0, n-1, last_occ + 1, r, parity)
            
            l = find_leftmost_zero(1, 0, n-1, 0, r)
            if l != -1:
                result = max(result, r - l + 1)
            
            last_occurrence[val] = r
        
        return result
# @lc code=end