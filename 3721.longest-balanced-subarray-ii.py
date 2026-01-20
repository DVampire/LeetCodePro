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
        first_pos = {}
        last_pos = {}
        for i in range(n):
            num = nums[i]
            if num not in first_pos:
                first_pos[num] = i
            last_pos[num] = i
        
        N = n
        M = 4 * (N + 2)
        tree_min = [0] * M
        tree_max = [0] * M
        lazy = [0] * M
        INF = n + 2
        
        def push(node: int, ns: int, ne: int) -> None:
            if lazy[node] != 0:
                tree_min[node] += lazy[node]
                tree_max[node] += lazy[node]
                if ns != ne:
                    lazy[2 * node] += lazy[node]
                    lazy[2 * node + 1] += lazy[node]
                lazy[node] = 0
        
        def update(node: int, ns: int, ne: int, l: int, r: int, val: int) -> None:
            push(node, ns, ne)
            if ns > r or ne < l:
                return
            if l <= ns and ne <= r:
                lazy[node] += val
                push(node, ns, ne)
                return
            mid = (ns + ne) // 2
            update(2 * node, ns, mid, l, r, val)
            update(2 * node + 1, mid + 1, ne, l, r, val)
            tree_min[node] = min(tree_min[2 * node], tree_min[2 * node + 1])
            tree_max[node] = max(tree_max[2 * node], tree_max[2 * node + 1])
        
        def find_leftmost(node: int, ns: int, ne: int, ql: int, qr: int) -> int:
            push(node, ns, ne)
            if ns > qr or ne < ql:
                return INF
            if tree_min[node] > 0 or tree_max[node] < 0:
                return INF
            if ns == ne:
                return ns
            mid = (ns + ne) // 2
            left_res = find_leftmost(2 * node, ns, mid, ql, qr)
            if left_res != INF:
                return left_res
            return find_leftmost(2 * node + 1, mid + 1, ne, ql, qr)
        
        ans = 0
        for r in range(n):
            num = nums[r]
            if num in first_pos and first_pos[num] == r:
                p = last_pos[num]
                s = 1 if num % 2 == 0 else -1
                update(1, 0, N, 0, p, s)
            min_l = find_leftmost(1, 0, N, 0, r + 1)
            if min_l < INF and min_l <= r:
                ans = max(ans, r - min_l + 1)
        return ans

# @lc code=end