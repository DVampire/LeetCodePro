#
# @lc app=leetcode id=3470 lang=python3
#
# [3470] Permutations IV
#

# @lc code=start
class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        MAX_K = 10**15 + 7
        fact = [1] * (n + 1)
        for i in range(2, n + 1):
            fact[i] = min(MAX_K, fact[i-1] * i)

        def count_ways(m, np, nq):
            # m slots left, first slot must be parity P (np elements available)
            # Sequence: P, Q, P, Q, ...
            # Number of P slots: (m + 1) // 2
            # Number of Q slots: m // 2
            if np == (m + 1) // 2 and nq == m // 2:
                if nq == 0:
                    return fact[np]
                if fact[np] > MAX_K // fact[nq]:
                    return MAX_K
                return fact[np] * fact[nq]
            return 0

        available_odds = [i for i in range(1, n + 1) if i % 2 != 0]
        available_evens = [i for i in range(1, n + 1) if i % 2 == 0]
        result = []
        last_parity = -1

        for i in range(n):
            found = False
            combined = sorted(available_odds + available_evens)
            for x in combined:
                if last_parity != -1 and (x % 2) == last_parity:
                    continue
                
                rem_odd = len(available_odds) - (1 if x % 2 != 0 else 0)
                rem_even = len(available_evens) - (1 if x % 2 == 0 else 0)
                m = rem_odd + rem_even
                
                if m == 0:
                    ways = 1
                else:
                    next_parity_needed = 1 - (x % 2)
                    if next_parity_needed == 1: # Next must be odd
                        ways = count_ways(m, rem_odd, rem_even)
                    else: # Next must be even
                        ways = count_ways(m, rem_even, rem_odd)
                
                if k <= ways:
                    result.append(x)
                    if x % 2 != 0:
                        available_odds.remove(x)
                    else:
                        available_evens.remove(x)
                    last_parity = x % 2
                    found = True
                    break
                else:
                    k -= ways
            
            if not found:
                return []
        
        return result
# @lc code=end