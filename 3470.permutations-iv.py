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
        for i in range(1, n + 1):
            fact[i] = fact[i - 1] * i
        
        odd_count = (n + 1) // 2
        even_count = n // 2
        
        def count_perms(odd_remaining, even_remaining, need_odd):
            total = odd_remaining + even_remaining
            if total == 0:
                return 1
            if need_odd:
                needed_odds = (total + 1) // 2
                needed_evens = total // 2
            else:
                needed_evens = (total + 1) // 2
                needed_odds = total // 2
            
            if odd_remaining == needed_odds and even_remaining == needed_evens:
                return fact[odd_remaining] * fact[even_remaining]
            return 0
        
        # Total number of alternating permutations
        total_perms = count_perms(odd_count, even_count, True) + count_perms(odd_count, even_count, False)
        
        if k > total_perms:
            return []
        
        result = []
        odds = list(range(1, n + 1, 2))
        evens = list(range(2, n + 1, 2))
        
        odd_remaining = odd_count
        even_remaining = even_count
        need_odd = None
        
        for pos in range(n):
            if pos == 0:
                available = sorted(odds + evens)
            elif need_odd:
                available = odds[:]
            else:
                available = evens[:]
            
            for num in available:
                is_odd = num % 2 == 1
                
                if is_odd:
                    perms = count_perms(odd_remaining - 1, even_remaining, False)
                else:
                    perms = count_perms(odd_remaining, even_remaining - 1, True)
                
                if perms >= k:
                    result.append(num)
                    if is_odd:
                        odds.remove(num)
                        odd_remaining -= 1
                        need_odd = False
                    else:
                        evens.remove(num)
                        even_remaining -= 1
                        need_odd = True
                    break
                else:
                    k -= perms
        
        return result
# @lc code=end