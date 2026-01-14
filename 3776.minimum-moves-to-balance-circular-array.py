#
# @lc app=leetcode id=3776 lang=python3
#
# [3776] Minimum Moves to Balance Circular Array
#

# @lc code=start
class Solution:
    def minMoves(self, balance: List[int]) -> int:
        n = len(balance)
        total = sum(balance)
        
        # Check if it's possible
        if total < 0:
            return -1
        
        # Find the negative position
        neg_idx = -1
        deficit = 0
        for i in range(n):
            if balance[i] < 0:
                neg_idx = i
                deficit = -balance[i]
                break
        
        # If no negative position, return 0
        if neg_idx == -1:
            return 0
        
        # Calculate distances from each position to neg_idx
        distances = []
        for i in range(n):
            if i == neg_idx or balance[i] <= 0:
                continue
            clockwise = (neg_idx - i + n) % n
            counterclockwise = (i - neg_idx + n) % n
            dist = min(clockwise, counterclockwise)
            distances.append((dist, balance[i]))
        
        # Sort by distance
        distances.sort()
        
        # Greedily transfer from closer positions
        total_cost = 0
        remaining_deficit = deficit
        for dist, amount in distances:
            transfer = min(amount, remaining_deficit)
            total_cost += transfer * dist
            remaining_deficit -= transfer
            if remaining_deficit == 0:
                break
        
        return total_cost
# @lc code=end