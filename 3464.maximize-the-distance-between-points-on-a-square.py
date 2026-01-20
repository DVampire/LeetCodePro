#
# @lc app=leetcode id=3464 lang=python3
#
# [3464] Maximize the Distance Between Points on a Square
#

# @lc code=start
class Solution:
    def maxDistance(self, side: int, points: List[List[int]], k: int) -> int:
        def get_t(x, y):
            # Map (x, y) to 1D coordinate t along the perimeter starting from (0,0)
            if y == 0 and 0 <= x < side:
                return x
            if x == side and 0 <= y < side:
                return side + y
            if y == side and 0 < x <= side:
                return 2 * side + (side - x)
            if x == 0 and 0 < y <= side:
                return 3 * side + (side - y)
            return 0

        pts = []
        for x, y in points:
            pts.append((get_t(x, y), x, y))
        
        # Sort points by their 1D position
        pts.sort(key=lambda p: p[0])
        n = len(pts)
        
        # Create doubled arrays to handle the cyclic nature easily
        T = [p[0] for p in pts] + [p[0] + 4 * side for p in pts]
        X = [p[1] for p in pts] + [p[1] for p in pts]
        Y = [p[2] for p in pts] + [p[2] for p in pts]
        
        def check(dist):
            # Precompute next_jump: next_jump[i] is the smallest index j >= i such that
            # the perimeter distance T[j] - T[i] >= dist.
            next_jump = [0] * (2 * n)
            right = 0
            for left in range(2 * n):
                if right < left: right = left
                while right < 2 * n and T[right] - T[left] < dist:
                    right += 1
                next_jump[left] = right
            
            # Try each point as a starting point
            for i in range(n):
                curr = i
                # Keep track of selected points' coordinates for distance checks
                sel_x = [X[i]]
                sel_y = [Y[i]]
                
                valid_sequence = True
                limit_t = T[i] + 4 * side
                
                for _ in range(k - 1):
                    cand = next_jump[curr]
                    found = False
                    
                    # Search for the next valid point
                    while cand < 2 * n and T[cand] < limit_t:
                        cx, cy = X[cand], Y[cand]
                        is_valid_cand = True
                        # Check Manhattan distance against all previously selected points
                        for j in range(len(sel_x)):
                            if abs(cx - sel_x[j]) + abs(cy - sel_y[j]) < dist:
                                is_valid_cand = False
                                break
                        
                        if is_valid_cand:
                            sel_x.append(cx)
                            sel_y.append(cy)
                            curr = cand
                            found = True
                            break
                        cand += 1
                    
                    if not found:
                        valid_sequence = False
                        break
                
                if valid_sequence:
                    return True
            return False

        # Binary search for the maximum minimum distance
        low = 1
        high = 2 * side
        ans = 1
        
        while low <= high:
            mid = (low + high) // 2
            if check(mid):
                ans = mid
                low = mid + 1
            else:
                high = mid - 1
                
        return ans
# @lc code=end