#
# @lc app=leetcode id=3579 lang=python3
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
from collections import Counter

class Solution:
    def minOperations(self, word1: str, word2: str) -> int:
        n = len(word1)
        # dp[i] = min operations to transform word1[:i] to word2[:i]
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        
        def get_transform_cost(s1, s2):
            # Cost without reverse
            # Calculate mismatches
            mismatches = 0
            pair_counts = Counter()
            
            for c1, c2 in zip(s1, s2):
                if c1 != c2:
                    mismatches += 1
                    pair_counts[(c1, c2)] += 1
            
            savings = 0
            # Find cross pairs (a, b) and (b, a) to swap
            # We iterate over the keys. To avoid double counting, we can process a pair only if a < b
            # or just process all and divide by 2? No, simpler to iterate copy of keys.
            # Actually, just iterate distinct pairs found.
            processed_pairs = set()
            for (a, b), count in pair_counts.items():
                if (a, b) in processed_pairs:
                    continue
                
                if (b, a) in pair_counts:
                    # We can form min(count[(a,b)], count[(b,a)]) swaps
                    # Each swap fixes 2 mismatches with 1 operation (instead of 2 replacements)
                    # So savings is 1 per swap.
                    num_swaps = min(count, pair_counts[(b, a)])
                    savings += num_swaps
                    processed_pairs.add((a, b))
                    processed_pairs.add((b, a))
            
            return mismatches - savings

        for i in range(1, n + 1):
            for j in range(i):
                # Substring from j to i-1
                sub1 = word1[j:i]
                sub2 = word2[j:i]
                
                # Option 1: No reverse on this chunk
                cost1 = get_transform_cost(sub1, sub2)
                
                # Option 2: Reverse this chunk
                # Cost is 1 (for reverse) + transform cost of reversed substring
                cost2 = 1 + get_transform_cost(sub1[::-1], sub2)
                
                current_chunk_cost = min(cost1, cost2)
                
                if dp[j] + current_chunk_cost < dp[i]:
                    dp[i] = dp[j] + current_chunk_cost
                    
        return dp[n]

# @lc code=end