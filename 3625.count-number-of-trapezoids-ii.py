#
# @lc app=leetcode id=3625 lang=python3
#
# [3625] Count Number of Trapezoids II
#

# @lc code=start
from math import gcd
from collections import defaultdict

class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        n = len(points)
        if n < 4:
            return 0
        
        # Structure: slope -> { intercept -> count_of_segments }
        # Slope is (dy, dx) reduced.
        # Intercept is dx*y - dy*x.
        slope_groups = defaultdict(lambda: defaultdict(int))
        
        # Structure: midpoint -> { slope -> count_of_segments }
        # Midpoint is (x1+x2, y1+y2)
        midpoint_groups = defaultdict(lambda: defaultdict(int))
        
        for i in range(n):
            for j in range(i + 1, n):
                x1, y1 = points[i]
                x2, y2 = points[j]
                
                # Calculate Slope
                dy = y2 - y1
                dx = x2 - x1
                
                g = gcd(dy, dx)
                dy //= g
                dx //= g
                
                # Normalize slope to handle signs consistently
                # Convention: dx > 0, or if dx == 0 then dy > 0
                if dx < 0:
                    dx = -dx
                    dy = -dy
                elif dx == 0:
                    if dy < 0:
                        dy = -dy
                
                slope = (dy, dx)
                
                # Calculate Intercept identifier
                # Line eq: dy*X - dx*Y + C = 0 => C = dx*Y - dy*X
                intercept = dx * y1 - dy * x1
                
                slope_groups[slope][intercept] += 1
                
                # Calculate Midpoint (doubled to stay integer)
                mx = x1 + x2
                my = y1 + y2
                midpoint_groups[(mx, my)][slope] += 1

        total_trapezoids_with_duplicates = 0
        
        # Calculate trapezoids based on parallel sides
        # A parallelogram is counted twice here (once for each pair of parallel sides)
        for slope, intercepts in slope_groups.items():
            counts = list(intercepts.values())
            if len(counts) < 2:
                continue
            
            sum_counts = sum(counts)
            sum_sq_counts = sum(c * c for c in counts)
            
            # Number of ways to pick two segments from different lines
            # (Sum^2 - Sum(c^2)) / 2
            pairs = (sum_counts * sum_counts - sum_sq_counts) // 2
            total_trapezoids_with_duplicates += pairs
            
        num_parallelograms = 0
        
        # Calculate parallelograms based on shared midpoints
        for midpoint, slopes in midpoint_groups.items():
            counts = list(slopes.values())
            if len(counts) < 2:
                continue
                
            sum_counts = sum(counts)
            # We need to choose 2 segments with DIFFERENT slopes sharing the same midpoint
            # Total pairs - pairs with same slope
            # Pairs with same slope are degenerate (collinear segments sharing midpoint -> collinear points)
            
            total_pairs = sum_counts * (sum_counts - 1) // 2
            degenerate_pairs = sum(c * (c - 1) // 2 for c in counts)
            
            num_parallelograms += (total_pairs - degenerate_pairs)
            
        # Total = (Generic Trapezoids) + 2 * (Parallelograms)
        # We want (Generic) + (Parallelograms)
        # So Result = Total_Calculated - Num_Parallelograms
        
        return total_trapezoids_with_duplicates - num_parallelograms

# @lc code=end