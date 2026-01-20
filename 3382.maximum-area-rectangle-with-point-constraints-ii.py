#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

from typing import List
from collections import defaultdict
from bisect import bisect_left, bisect_right

# @lc code=start
class MergeSortTree:
    def __init__(self, ys_lists: List[List[int]]):
        self.n = len(ys_lists)
        self.tree = [[] for _ in range(4 * self.n)]
        self._build(1, 0, self.n - 1, ys_lists)

    def _build(self, node: int, start: int, end: int, ys_lists: List[List[int]]):
        if start == end:
            self.tree[node] = ys_lists[start][:]
            return
        mid = (start + end) // 2
        self._build(2 * node, start, mid, ys_lists)
        self._build(2 * node + 1, mid + 1, end, ys_lists)
        left = self.tree[2 * node]
        right = self.tree[2 * node + 1]
        i = j = 0
        merged = []
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                merged.append(left[i])
                i += 1
            else:
                merged.append(right[j])
                j += 1
        merged.extend(left[i:])
        merged.extend(right[j:])
        self.tree[node] = merged

    def query(self, node: int, start: int, end: int, qleft: int, qright: int, ylow: int, yhigh: int) -> int:
        if qright < start or end < qleft:
            return 0
        if qleft <= start and end <= qright:
            return bisect_right(self.tree[node], yhigh) - bisect_left(self.tree[node], ylow)
        mid = (start + end) // 2
        left_count = self.query(2 * node, start, mid, qleft, qright, ylow, yhigh)
        right_count = self.query(2 * node + 1, mid + 1, end, qleft, qright, ylow, yhigh)
        return left_count + right_count

class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        n = len(xCoord)
        ys_dict = defaultdict(list)
        for i in range(n):
            ys_dict[xCoord[i]].append(yCoord[i])
        X = sorted(ys_dict.keys())
        m = len(X)
        if m < 2:
            return -1
        ys_lists = [sorted(ys_dict[X[i]]) for i in range(m)]
        mst = MergeSortTree(ys_lists)
        segments = defaultdict(list)
        for i in range(m):
            ys = ys_lists[i]
            for k in range(len(ys) - 1):
                yb = ys[k]
                yt = ys[k + 1]
                segments[(yb, yt)].append(i)
        max_area = 0
        for (yb, yt), supp in segments.items():
            if len(supp) < 2:
                continue
            height = yt - yb
            for t in range(len(supp) - 1):
                li = supp[t]
                ri = supp[t + 1]
                L = li + 1
                R = ri - 1
                width = X[ri] - X[li]
                if L > R:
                    area = width * height
                    if area > max_area:
                        max_area = area
                    continue
                cnt = mst.query(1, 0, m - 1, L, R, yb, yt)
                if cnt == 0:
                    area = width * height
                    if area > max_area:
                        max_area = area
        return max_area if max_area > 0 else -1

# @lc code=end
