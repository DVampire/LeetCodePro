#
# @lc app=leetcode id=3579 lang=python3
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
class Solution:
    def minOperations(self, word1: str, word2: str) -> int:
        n = len(word1)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        def get_cost(s, t):
            length = len(s)
            
            def calc_ops(s_curr, t_curr):
                mismatches = 0
                counts = {} # Stores pairs (char_in_s, char_in_t)
                for i in range(len(s_curr)):
                    if s_curr[i] != t_curr[i]:
                        mismatches += 1
                        pair = (s_curr[i], t_curr[i])
                        counts[pair] = counts.get(pair, 0) + 1
                
                n2cycle = 0
                chars = list(set([p[0] for p in counts.keys()] + [p[1] for p in counts.keys()]))
                for i in range(len(chars)):
                    for j in range(i + 1, len(chars)):
                        c1, c2 = chars[i], chars[j]
                        n2cycle += min(counts.get((c1, c2), 0), counts.get((c2, c1), 0))
                
                return mismatches - n2cycle

            # Option 1: No reverse
            cost1 = calc_ops(s, t)
            # Option 2: With reverse
            cost2 = 1 + calc_ops(s[::-1], t)
            
            return min(cost1, cost2)

        # Precompute substring costs to optimize
        costs = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n):
            for j in range(i + 1, n + 1):
                costs[i][j] = get_cost(word1[i:j], word2[i:j])

        for i in range(1, n + 1):
            for j in range(i):
                dp[i] = min(dp[i], dp[j] + costs[j][i])
        
        return int(dp[n])
# @lc code=end