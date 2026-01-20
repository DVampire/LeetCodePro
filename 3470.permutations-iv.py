#
# @lc app=leetcode id=3470 lang=python3
#
# [3470] Permutations IV
#

# @lc code=start
class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        # Precompute factorials
        fact = [1] * (n + 1)
        for i in range(2, n + 1):
            fact[i] = fact[i - 1] * i

        # Initial counts
        odd_count = (n + 1) // 2
        even_count = n // 2
        
        # Calculate total possible alternating permutations to check feasibility quickly
        # Or simpler: just run the logic. If we can't find the k-th, return [].
        # However, checking total count helps handle the "return empty list" case cleanly.
        
        def count_ways(o, e, next_parity):
            # Returns number of ways to form alternating sequence of length (o+e)
            # starting with parity `next_parity` (1 for odd, 0 for even)
            # Pattern is fixed based on start.
            length = o + e
            if length == 0: return 1
            
            needed_o = 0
            needed_e = 0
            
            if next_parity == 1: # Start with Odd: O, E, O, E...
                needed_o = (length + 1) // 2
                needed_e = length // 2
            else: # Start with Even: E, O, E, O...
                needed_o = length // 2
                needed_e = (length + 1) // 2
            
            if o == needed_o and e == needed_e:
                return fact[o] * fact[e]
            return 0

        # Initial check
        # We can start with Odd or Even if n is even. If n is odd, must start with Odd.
        # But inside the loop logic, this is handled naturally by trying 1..n
        
        total_ways = 0
        if n % 2 == 1:
            # Must start with Odd
            total_ways = count_ways(odd_count, even_count, 1)
        else:
            # Can start with Odd or Even
            total_ways = count_ways(odd_count, even_count, 1) + count_ways(odd_count, even_count, 0)
            
        if k > total_ways:
            return []
        
        result = []
        used = [False] * (n + 1)
        
        # Current available counts
        cur_odds = odd_count
        cur_evens = even_count
        
        last_val = -1 # No previous value
        
        for i in range(n):
            found = False
            # Try placing number x at position i
            for x in range(1, n + 1):
                if used[x]:
                    continue
                
                # Check alternating condition
                is_odd = (x % 2 != 0)
                if last_val != -1:
                    last_odd = (last_val % 2 != 0)
                    if is_odd == last_odd:
                        continue
                
                # Check if valid remaining configuration exists
                rem_o = cur_odds - (1 if is_odd else 0)
                rem_e = cur_evens - (1 if not is_odd else 0)
                
                # Next position must have opposite parity
                next_parity = 0 if is_odd else 1
                
                ways = count_ways(rem_o, rem_e, next_parity)
                
                if k <= ways:
                    # x is the correct number
                    result.append(x)
                    used[x] = True
                    cur_odds = rem_o
                    cur_evens = rem_e
                    last_val = x
                    found = True
                    break
                else:
                    k -= ways
            
            if not found:
                return []
                
        return result
# @lc code=end