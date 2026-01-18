#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
from collections import defaultdict
from bisect import bisect_left

class FenwickTree:
    def __init__(self, n):
        self.tree = [0] * (n + 1)

    def update(self, i, delta):
        i += 1
        while i < len(self.tree):
            self.tree[i] += delta
            i += i & (-i)

    def query(self, i):
        i += 1
        s = 0
        while i > 0:
            s += self.tree[i]
            i -= i & (-i)
        return s

    def query_range(self, left, right):
        if left > right:
            return 0
        return self.query(right) - self.query(left - 1)

class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        points_by_x = defaultdict(list)
        all_y = set()
        for x, y in zip(xCoord, yCoord):
            points_by_x[x].append(y)
            all_y.add(y)
        
        sorted_y = sorted(list(all_y))
        y_map = {y: i for i, y in enumerate(sorted_y)}
        
        sorted_x = sorted(points_by_x.keys())
        bit = FenwickTree(len(sorted_y))
        last_seen = {} # (y_low, y_high) -> (x_prev, count_at_x_prev)
        max_area = -1

        for x in sorted_x:
            ys = sorted(points_by_x[x])
            
            # Check pairs at current x before updating BIT
            for i in range(len(ys) - 1):
                y_low, y_high = ys[i], ys[i+1]
                y_low_idx, y_high_idx = y_map[y_low], y_map[y_high]
                
                # Current count of points in range [y_low, y_high] seen in previous x-coordinates
                count_before = bit.query_range(y_low_idx, y_high_idx)
                
                if (y_low, y_high) in last_seen:
                    prev_x, prev_count = last_seen[(y_low, y_high)]
                    # If count increased by exactly 2, no points are in between
                    if count_before == prev_count + 2:
                        area = (x - prev_x) * (y_high - y_low)
                        if area > max_area:
                            max_area = area
                
                # Update last_seen with current x and count
                last_seen[(y_low, y_high)] = (x, count_before)
            
            # Now add all points at this x to the BIT
            for y in ys:
                bit.update(y_map[y], 1)

        return max_area
# @lc code=end