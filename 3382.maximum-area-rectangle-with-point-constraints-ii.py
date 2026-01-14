#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
from collections import defaultdict
from typing import List

class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        n = len(xCoord)
        if n < 4:
            return -1
        
        xs = sorted(set(xCoord))
        ys = sorted(set(yCoord))
        x_comp = {x: i for i, x in enumerate(xs)}
        y_comp = {y: i for i, y in enumerate(ys)}
        Y = len(ys)
        
        points_by_x = defaultdict(list)
        for i in range(n):
            points_by_x[xCoord[i]].append(yCoord[i])
        for x in points_by_x:
            points_by_x[x].sort()
        
        segment_occurrences = defaultdict(list)
        for x in xs:
            ys_in_col = points_by_x[x]
            x_idx = x_comp[x]
            for i in range(len(ys_in_col) - 1):
                y1, y2 = ys_in_col[i], ys_in_col[i + 1]
                segment_occurrences[(y1, y2)].append((x, x_idx))
        
        rectangles = []
        for (y1, y2), occurrences in segment_occurrences.items():
            for i in range(len(occurrences) - 1):
                x_prev, x_prev_idx = occurrences[i]
                x, x_idx = occurrences[i + 1]
                rectangles.append((x_prev_idx, x_idx, y_comp[y1], y_comp[y2], x, x_prev, y1, y2))
        
        if not rectangles:
            return -1
        
        events = []
        for x in xs:
            x_idx = x_comp[x]
            for y in points_by_x[x]:
                events.append((x_idx, 0, y_comp[y], -1, -1, 0))
        
        for rect_id, (x_prev_idx, x_idx, y1_idx, y2_idx, _, _, _, _) in enumerate(rectangles):
            events.append((x_idx - 1, 1, y1_idx, y2_idx, rect_id, 1))
            events.append((x_prev_idx, 1, y1_idx, y2_idx, rect_id, -1))
        
        events.sort()
        
        bit = [0] * (Y + 1)
        
        def bit_update(i):
            i += 1
            while i <= Y:
                bit[i] += 1
                i += i & (-i)
        
        def bit_query(i):
            if i < 0:
                return 0
            i += 1
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & (-i)
            return s
        
        def bit_range_query(l, r):
            return bit_query(r) - bit_query(l - 1)
        
        results = [0] * len(rectangles)
        
        for event in events:
            if event[1] == 0:
                bit_update(event[2])
            else:
                _, _, y1_idx, y2_idx, rect_id, sign = event
                results[rect_id] += sign * bit_range_query(y1_idx, y2_idx)
        
        max_area = -1
        for rect_id, (_, _, _, _, x, x_prev, y1, y2) in enumerate(rectangles):
            if results[rect_id] == 0:
                area = (x - x_prev) * (y2 - y1)
                max_area = max(max_area, area)
        
        return max_area
# @lc code=end