#
# @lc app=leetcode id=3725 lang=python3
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#

from typing import List

# @lc code=start
class Solution:
    def countCoprime(self, mat: List[List[int]]) -> int:
        MOD = 10**9 + 7
        MAXV = 150

        # Precompute divisors for each value up to MAXV
        divisors = [[] for _ in range(MAXV + 1)]
        for d in range(1, MAXV + 1):
            for k in range(d, MAXV + 1, d):
                divisors[k].append(d)

        # Compute Möbius function mu[1..MAXV] using linear sieve
        mu = [0] * (MAXV + 1)
        mu[1] = 1
        primes = []
        is_comp = [False] * (MAXV + 1)
        for i in range(2, MAXV + 1):
            if not is_comp[i]:
                primes.append(i)
                mu[i] = -1
            for p in primes:
                if i * p > MAXV:
                    break
                is_comp[i * p] = True
                if i % p == 0:
                    mu[i * p] = 0
                    break
                else:
                    mu[i * p] = -mu[i]

        # ways[d] = product over rows of (count of elements divisible by d)
        ways = [1] * (MAXV + 1)
        for row in mat:
            cnt = [0] * (MAXV + 1)
            for x in row:
                for d in divisors[x]:
                    cnt[d] += 1
            for d in range(1, MAXV + 1):
                ways[d] = (ways[d] * cnt[d]) % MOD

        ans = 0
        for d in range(1, MAXV + 1):
            if mu[d] == 0:
                continue
            ans = (ans + mu[d] * ways[d]) % MOD

        return ans % MOD
# @lc code=end
