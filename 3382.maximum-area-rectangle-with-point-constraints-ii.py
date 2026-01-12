#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
import collections

class FenwickTree:
    def __init__(self, n):
        self.tree = [0] * (n + 1)

    def update(self, i, delta):
        while i < len(self.tree):
            self.tree[i] += delta
            i += i & (-i)

    def query(self, i):
        s = 0
        while i > 0:
            s += self.tree[i]
            i -= i & (-i)
        return s

    def query_range(self, l, r):
        if l > r: return 0
        return self.query(r) - self.query(l - 1)

class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        points_by_x = collections.defaultdict(list)
        all_y = set()
        for x, y in zip(xCoord, yCoord):
            points_by_x[x].append(y)
            all_y.add(y)
        
        unique_ys = sorted(list(all_y))
        y_map = {y: i + 1 for i, y in enumerate(unique_ys)}
        
        sorted_xs = sorted(points_by_x.keys())
        bit = FenwickTree(len(unique_ys))
        history = {} # (y_low, y_high) -> (last_x, count_at_last_x)
        max_area = -1
        
        for x in sorted_xs:
            ys = sorted(points_by_x[x])
            
            # Check for rectangles ending at this x
            for i in range(len(ys) - 1):
                y_low, y_high = ys[i], ys[i+1]
                idx_low, idx_high = y_map[y_low], y_map[y_high]
                
                # Number of points seen so far in this y-range (before current x's points)
                current_cnt = bit.query_range(idx_low, idx_high)
                
                pair = (y_low, y_high)
                if pair in history:
                    prev_x, prev_cnt = history[pair]
                    # If count matches, no points were added in this range between prev_x and current_x
                    if current_cnt == prev_cnt:
                        area = (x - prev_x) * (y_high - y_low)
                        if area > max_area:
                            max_area = area
                
                # Update history for this segment
                # prev_cnt is current_cnt + 2 (the two points we will add for current x)
                history[pair] = (x, current_cnt + 2)
            
            # Add all points at this x to the Fenwick tree
            for y in ys:
                bit.update(y_map[y], 1)
        
        return max_area
# @lc code=end