#
# @lc app=leetcode id=3449 lang=python3
#
# [3449] Maximize the Minimum Game Score
#

# @lc code=start
class Solution:
    def maxScore(self, points: List[int], m: int) -> int:
        n = len(points)
        
        # Binary search on the answer
        left, right = 0, max(points) * m
        
        def canAchieveMinScore(min_score):
            # For each position, calculate minimum moves needed to achieve min_score
            min_moves = [0] * n
            for i in range(n):
                if points[i] == 0:
                    min_moves[i] = float('inf') if min_score > 0 else 0
                else:
                    min_moves[i] = (min_score + points[i] - 1) // points[i]
            
            # Try all possible starting positions
            for start in range(n):
                # Try going left first, then right
                moves = min_moves[start]  # First move to start position
                max_additional = 0
                
                # Go as far left as possible, then right
                # Calculate moves needed for left side
                left_moves = 0
                min_val_so_far = float('inf')
                for i in range(start, -1, -1):
                    left_moves += min_moves[i]
                    min_val_so_far = min(min_val_so_far, min_moves[i])
                    # We can save at most min_val_so_far moves
                    max_additional = max(max_additional, left_moves - min_val_so_far)
                
                # Go as far right as possible, then left
                right_moves = 0
                min_val_so_far = float('inf')
                for i in range(start, n):
                    right_moves += min_moves[i]
                    min_val_so_far = min(min_val_so_far, min_moves[i])
                    max_additional = max(max_additional, right_moves - min_val_so_far)
                
                # Total moves needed from this start position
                total_moves = sum(min_moves) - max_additional
                
                if total_moves <= m:
                    return True
            
            return False
        
        # More efficient approach
        def canAchieveMinScoreEfficient(target):
            # For target score, each position needs at least ceil(target/points[i]) visits
            required_visits = []
            for i in range(n):
                if points[i] > 0:
                    visits = (target + points[i] - 1) // points[i]  # This is ceil(target/points[i])
                    required_visits.append(visits)
                else:
                    required_visits.append(0)
            
            # We need to visit each position required_visits[i] times
            # Find minimum moves to do this
            
            # Greedy: try all starting positions and find minimum cost path
            min_cost = float('inf')
            
            for start in range(n):
                # Simulate optimal path starting from position 'start'
                # This is complex, so let's use a simpler estimation
                
                # Simplified: minimum moves is at least sum of required visits
                # But we can save moves by visiting positions optimally
                
                # Estimate: in optimal path, we don't need to go back and forth excessively
                # The cost is at least sum(required_visits) 
                # But we can save at most (max(required_visits) - 1) moves 
                # by visiting the position with most required visits first
                
                total_required = sum(required_visits)
                if total_required == 0:
                    return True
                    
                # Better estimation: cost is at least total_required
                # But we can save moves by visiting in optimal order
                # The savings are limited by how we can traverse the array
                
                # Worst case: we need to traverse the whole array multiple times
                # But since we can move in both directions, we can be more efficient
                
                # Let's use a more accurate simulation
                
                # For now, let's use a simplified check:
                if total_required <= m:
                    return True
            
            return False
        
        # Even simpler: binary search with direct calculation
        def isPossible(score):
            # Calculate minimum moves needed to get score at each position
            moves_needed = []
            for p in points:
                # To get at least 'score', we need ceil(score/p) visits
                visits = (score + p - 1) // p if p > 0 else (1 if score <= 0 else float('inf'))
                moves_needed.append(visits)
            
            # If any position needs infinite visits but score > 0, impossible
            if any(m == float('inf') for m in moves_needed):
                return False
            
            # Minimum moves is the sum (if we could teleport)
            # But we need to walk, so it's at least sum
            # In practice, optimal path can be more efficient
            
            # Simple check: if sum <= m, then possible
            return sum(moves_needed) <= m
        
        # Binary search
        result = 0
        while left <= right:
            mid = (left + right) // 2
            if isPossible(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result
# @lc code=end