#
# @lc app=leetcode id=3382 lang=python3
#
# [3382] Maximum Area Rectangle With Point Constraints II
#

# @lc code=start
class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        # Combine coordinates into points
        points = sorted(zip(xCoord, yCoord))
        n = len(points)
        
        # Coordinate compression for Y
        unique_ys = sorted(list(set(yCoord)))
        y_map = {y: i for i, y in enumerate(unique_ys)}
        m = len(unique_ys)
        
        # Segment Tree for Range Maximum Query
        # We store the last seen x-index (from the unique_xs list) for each y-rank.
        # Initialize with -1.
        tree = [-1] * (4 * m)
        
        def update(node, start, end, idx, val):
            if start == end:
                tree[node] = val
                return
            mid = (start + end) // 2
            if idx <= mid:
                update(2 * node, start, mid, idx, val)
            else:
                update(2 * node + 1, mid + 1, end, idx, val)
            tree[node] = max(tree[2 * node], tree[2 * node + 1])
            
        def query(node, start, end, L, R):
            if R < start or end < L:
                return -1
            if L <= start and end <= R:
                return tree[node]
            mid = (start + end) // 2
            return max(query(2 * node, start, mid, L, R),
                       query(2 * node + 1, mid + 1, end, L, R))
        
        # Group points by x-coordinate
        from collections import defaultdict
        points_by_x = defaultdict(list)
        for x, y in points:
            points_by_x[x].append(y)
            
        # Sort unique x coordinates to iterate in order
        sorted_unique_xs = sorted(points_by_x.keys())
        
        # Map to store the last x-coordinate where a specific segment (y1, y2) was seen
        # Key: (y1, y2), Value: x_coordinate
        # Note: We store the actual x-coordinate value for area calculation,
        # but the segment tree stores indices of sorted_unique_xs.
        last_seen_segment_x = {}
        
        max_area = -1
        
        for i, x in enumerate(sorted_unique_xs):
            ys = points_by_x[x]
            # ys is already sorted because we sorted 'points' initially and insertion order is preserved
            # or we can explicitly sort to be safe
            ys.sort()
            
            # Check segments formed by consecutive y-coordinates
            for j in range(len(ys) - 1):
                y1, y2 = ys[j], ys[j+1]
                
                if (y1, y2) in last_seen_segment_x:
                    prev_x = last_seen_segment_x[(y1, y2)]
                    # We need the index of prev_x in sorted_unique_xs to compare with seg tree results
                    # Since we don't store the index in the map, we might need a way to look it up
                    # OR, we can store (prev_x, prev_x_index) in the map.
                    # Let's refine the map: Key=(y1, y2), Value=(x_val, x_index)
                    
                    # However, looking at the logic: 
                    # We just need to know if there's any point in y-range [y1, y2] 
                    # that appeared strictly after prev_x_index.
                    
                    # Let's re-fetch the stored data properly.
                    pass
            
            # Re-iterate to process logic correctly
            pass
        
        # Reset and implement the loop cleanly
        last_seen_segment = {} # (y1, y2) -> (x_val, x_index)
        
        for i, x in enumerate(sorted_unique_xs):
            ys = points_by_x[x]
            ys.sort()
            
            # 1. Query and Check candidates
            for j in range(len(ys) - 1):
                y1, y2 = ys[j], ys[j+1]
                rank1, rank2 = y_map[y1], y_map[y2]
                
                if (y1, y2) in last_seen_segment:
                    prev_x, prev_x_idx = last_seen_segment[(y1, y2)]
                    
                    # Check if any point exists in y-range [y1, y2] strictly after prev_x_idx
                    # The segment tree stores the max x-index seen so far for a y-rank.
                    # If max_idx > prev_x_idx, it means there is an obstruction.
                    max_idx_in_range = query(1, 0, m - 1, rank1, rank2)
                    
                    if max_idx_in_range <= prev_x_idx:
                        area = (x - prev_x) * (y2 - y1)
                        if area > max_area:
                            max_area = area
                    
                    # Even if invalid, we update the last seen for this segment to current
                    # because the old one can't form a valid rectangle with any future line 
                    # if the current line blocked it or if it was valid (greedy approach for segments)
                    # Actually, for the specific pair (y1, y2), the current vertical line 
                    # becomes the new potential left edge for future rectangles.
                    
                # Update the map for this segment to be the current x
                last_seen_segment[(y1, y2)] = (x, i)
            
            # 2. Update Segment Tree with current points
            # We must do this AFTER checking segments to avoid self-interference
            for y in ys:
                update(1, 0, m - 1, y_map[y], i)
                
        return max_area
# @lc code=end