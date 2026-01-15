#
# @lc app=leetcode id=3449 lang=python3
#
# [3449] Maximize the Minimum Game Score
#

from typing import List
import math

# @lc code=start
class Solution:
    
    def _required_moves(self, required):
        """
        Estimate minimum additional moves needed given required visits.
        Uses idea of transporting "demands" along line.
        """
        n = len(required)
        # Find leftmost and rightmost indices with positive requirement
        left = None
        right = None
        tot_req = 0
        weighted_sum = 0
        
        for i in range(n):
            if required[i] > 0:
                tot_req += required[i]
                weighted_sum += required[i] * i
                if left is None:
                    left = i
                right = i
        
        # No positive requirement
        if tot_req == 0:
            return 0
        
        # Every positive requirement contributes.
        # Minimum movements include:
        #   - Traveling to cover spread.
        #   - Multiple passes.
        
        # Conservative estimate:
        #   At least tot_req moves just for depositing.
        #   Additional travel overhead.
        
        # Starting position is index 0.
        overhead = max(0, right - left)
        
        # Simplified heuristic:
        estimated_moves = tot_req + overhead
        
        return estimated_moves
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
def _feasible(self,t,move_limit):
        """
        Check whether target minimum score t can be achieved.
        """
        pts=self.points
        n=self.n
        
        # Required visits
        req=[(t+p-)//p for p in pts]
        
        # Account for mandatory first move
        req[01]-=
        if req[01]<:
            req[01]=
            
        tot_req_sum(req)
        
        # Available moves after mandatory first
        avail_move_limit-
        
        if tot_req>avail_move:
            return False
            
        est_move=self._required_moves(req)
            
            est_move<=
avail_move
            returne True
            else:
                returne False
                