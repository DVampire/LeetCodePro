#
# @lc app=leetcode id=3525 lang=python3
#
# [3525] Find X Value of Array II
#

# @lc code=start
from typing import List

class Solution:
    def resultArray(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        a = [x % k for x in nums]

        tree = [None] * (4 * n + 10)

        def merge(left, right):
            res = [0] * (k + 1)
            res[0] = (left[0] * right[0]) % k
            for i in range(k):
                res[i + 1] = left[i + 1]
            for t in range(k):
                target = (left[0] * t) % k
                res[target + 1] += right[t + 1]
            return res

        def build(node, start, end):
            if start == end:
                p = a[start]
                tree[node] = [0] * (k + 1)
                tree[node][0] = p
                tree[node][p + 1] = 1
                return
            mid = (start + end) // 2
            build(2 * node, start, mid)
            build(2 * node + 1, mid + 1, end)
            tree[node] = merge(tree[2 * node], tree[2 * node + 1])

        def update(node, start, end, idx, val):
            if start == end:
                tree[node] = [0] * (k + 1)
                tree[node][0] = val
                tree[node][val + 1] = 1
                return
            mid = (start + end) // 2
            if idx <= mid:
                update(2 * node, start, mid, idx, val)
            else:
                update(2 * node + 1, mid + 1, end, idx, val)
            tree[node] = merge(tree[2 * node], tree[2 * node + 1])

        def query(node, start, end, l, r):
            if r < start or end < l:
                iden = [0] * (k + 1)
                iden[0] = 1
                return iden
            if l <= start and end <= r:
                return tree[node]
            mid = (start + end) // 2
            leftq = query(2 * node, start, mid, l, r)
            rightq = query(2 * node + 1, mid + 1, end, l, r)
            return merge(leftq, rightq)

        build(1, 0, n - 1)

        ans = []
        for qi in queries:
            indexi, valuei, starti, xi = qi
            new_val = valuei % k
            update(1, 0, n - 1, indexi, new_val)
            qnode = query(1, 0, n - 1, starti, n - 1)
            ans.append(qnode[xi + 1])
        return ans
# @lc code=end